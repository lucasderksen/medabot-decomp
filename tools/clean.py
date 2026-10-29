"""Remove only this project's generated build directory."""

import shutil

from common import ROOT

target = ROOT / "build"
if target.exists():
    if target.is_symlink() or target.resolve() != ROOT.resolve() / "build":
        raise SystemExit(f"Refusing to remove a redirected build directory: {target}")
    shutil.rmtree(target)
    print(f"Removed {target}")
