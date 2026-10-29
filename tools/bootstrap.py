"""Download the pinned portable Arm toolchain into this project (no installer)."""

import argparse
import hashlib
from pathlib import Path
import platform
import subprocess
import sys
import urllib.request
import zipfile

ROOT = Path(__file__).resolve().parents[1]
ARCHIVE = "arm-gnu-toolchain-14.3.rel1-mingw-w64-x86_64-arm-none-eabi.zip"
URL = "https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu/14.3.rel1/binrel/" + ARCHIVE
SHA256 = "864c0c8815857d68a1bbba2e5e2782255bb922845c71c97636004a3d74f60986"
M2C_UPSTREAM = "https://github.com/matt-kempster/m2c.git"
M2C_COMMIT = "708d2d2cb2698f091a92492b328f73b24209f72d"
PERMUTER_UPSTREAM = "https://github.com/WhenGryphonsFly/decomp-permuter-agbcc.git"
PERMUTER_COMMIT = "1f7ef872b12f54db7678ff00e0346abc015410ae"


def bootstrap_toolchain():
    if platform.system() != "Windows" or platform.machine().lower() not in ("amd64", "x86_64"):
        raise SystemExit("This bootstrap downloads Windows x64 tools. On other hosts install arm-none-eabi tools and set ARM_TOOLCHAIN to their bin directory.")
    destination = ROOT / "tools" / "toolchain"
    compiler = destination / "bin" / "arm-none-eabi-gcc.exe"
    if compiler.exists():
        subprocess.run([str(compiler), "--version"], check=True)
        return
    downloads = ROOT / "tools" / "downloads"
    downloads.mkdir(parents=True, exist_ok=True)
    archive = downloads / ARCHIVE
    if not archive.exists():
        partial = archive.with_suffix(".zip.part")
        print(f"Downloading {URL}", flush=True)
        with urllib.request.urlopen(URL, timeout=60) as response, partial.open("wb") as output:
            total = int(response.headers.get("Content-Length", "0"))
            size = 0
            last_report = 0
            while chunk := response.read(1024 * 1024):
                output.write(chunk)
                size += len(chunk)
                if size - last_report >= 25 * 1024 * 1024:
                    print(f"  {size // (1024 * 1024)} / {total // (1024 * 1024)} MiB", flush=True)
                    last_report = size
        partial.replace(archive)
    with archive.open("rb") as source:
        digest = hashlib.file_digest(source, "sha256").hexdigest()
    if digest != SHA256:
        raise SystemExit(f"Archive checksum mismatch: {digest}; remove {archive} and retry.")
    print(f"Verified SHA-256: {digest}", flush=True)
    destination.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(archive) as bundle:
        members = bundle.infolist()
        prefix = members[0].filename.split("/")[0] + "/"
        for member in members:
            relative = member.filename.removeprefix(prefix)
            if not relative:
                continue
            target = (destination / relative).resolve()
            if not target.is_relative_to(destination.resolve()):
                raise SystemExit(f"Unsafe archive path: {member.filename}")
            if member.is_dir():
                target.mkdir(parents=True, exist_ok=True)
            else:
                target.parent.mkdir(parents=True, exist_ok=True)
                with bundle.open(member) as source, target.open("wb") as output:
                    while chunk := source.read(1024 * 1024):
                        output.write(chunk)
    subprocess.run([str(compiler), "--version"], check=True)


def checkout(name, upstream, commit):
    """Check out a pinned commit of a pure-Python tool into tools/downloads/<name>."""
    destination = ROOT / "tools" / "downloads" / name
    if not (destination / ".git").exists():
        destination.mkdir(parents=True, exist_ok=True)
        subprocess.run(["git", "init", "-q", str(destination)], check=True)
        subprocess.run(["git", "-C", str(destination), "remote", "add", "origin", upstream], check=True)
    subprocess.run(["git", "-C", str(destination), "fetch", "-q", "--depth", "1", "origin", commit], check=True)
    subprocess.run(["git", "-C", str(destination), "checkout", "-q", "--detach", commit], check=True)
    print(f"{name} {commit[:12]} in {destination}", flush=True)


def bootstrap_m2c():
    checkout("m2c", M2C_UPSTREAM, M2C_COMMIT)


def bootstrap_permuter():
    checkout("permuter", PERMUTER_UPSTREAM, PERMUTER_COMMIT)
    subprocess.run([sys.executable, "-m", "pip", "--isolated", "install", "--index-url", "https://pypi.org/simple", "--target",
                    str(ROOT / "tools" / "python"), "pycparser==2.22", "toml==0.10.2"], check=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--analysis", action="store_true", help="Also install pinned Capstone into tools/python")
    parser.add_argument("--emulation", action="store_true", help="Also install pinned Unicorn for isolated CPU checks")
    parser.add_argument("--m2c", action="store_true", help="Also check out the pinned m2c decompiler for tools/m2c_candidate.py")
    parser.add_argument("--permuter", action="store_true", help="Also check out decomp-permuter-agbcc for tools/permute.py")
    args = parser.parse_args()
    bootstrap_toolchain()
    if args.m2c:
        bootstrap_m2c()
    if args.permuter:
        bootstrap_permuter()
    if args.analysis:
        subprocess.run([sys.executable, "-m", "pip", "--isolated", "install", "--index-url", "https://pypi.org/simple", "--target", str(ROOT / "tools" / "python"), "capstone==5.0.6"], check=True)
    if args.emulation:
        subprocess.run([sys.executable, "-m", "pip", "--isolated", "install", "--index-url", "https://pypi.org/simple", "--target", str(ROOT / "tools" / "python"), "unicorn==2.1.4"], check=True)


if __name__ == "__main__":
    main()
