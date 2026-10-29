"""Create or remove an isolated git worktree for one agent.

Each worktree gets its own branch and its own build/ directory, so parallel
agents never overwrite each other's experiments. The ignored, project-local
toolchain directories are linked (directory junctions on Windows) and the
reference ROM is hard-linked, so nothing is downloaded or copied again.

    python tools/worktree.py create compiler_input
    python tools/worktree.py remove compiler_input
"""

import argparse
import os
import subprocess
import sys
from pathlib import Path

from common import ROOT

WORKTREES = ROOT.parent / f"{ROOT.name}-worktrees"
LINKED_DIRS = ("tools/toolchain", "tools/downloads", "tools/python")
LINKED_FILES = ("baserom.gba",)


def git(*args):
    subprocess.run(["git", "-C", str(ROOT), *args], check=True)


def link_dir(source, target):
    if os.name == "nt":
        subprocess.run(["cmd", "/c", "mklink", "/J", str(target), str(source)], check=True, stdout=subprocess.DEVNULL)
    else:
        target.symlink_to(source, target_is_directory=True)


def create(name, base):
    path = WORKTREES / name
    if path.exists():
        raise SystemExit(f"{path} already exists.")
    git("worktree", "add", "-b", f"work/{name}", str(path), base)
    for relative in LINKED_DIRS:
        if (ROOT / relative).is_dir():
            link_dir(ROOT / relative, path / relative)
    for relative in LINKED_FILES:
        if (ROOT / relative).is_file():
            os.link(ROOT / relative, path / relative)
    print(f"Worktree {path} on branch work/{name}.")
    print("Run python tools/build.py there once: tools/match.py resolves symbols from its own build/medabots.elf.")


def remove(name):
    path = WORKTREES / name
    # Unlink shared directories first so removal can never reach their targets.
    for relative in LINKED_DIRS:
        link = path / relative
        if link.exists() or link.is_symlink():
            os.unlink(link) if link.is_symlink() else os.rmdir(link)
    git("worktree", "remove", "--force", str(path))
    print(f"Removed {path}; branch work/{name} is kept.")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    commands = parser.add_subparsers(dest="command", required=True)
    create_parser = commands.add_parser("create")
    create_parser.add_argument("name", help="Agent identity, e.g. compiler_input")
    create_parser.add_argument("--base", default="main")
    commands.add_parser("remove").add_argument("name")
    args = parser.parse_args()
    if args.command == "create":
        create(args.name, args.base)
    else:
        remove(args.name)


if __name__ == "__main__":
    sys.exit(main())
