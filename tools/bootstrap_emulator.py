"""Download the optional pinned Windows x64 mGBA libretro research core."""

import hashlib
from pathlib import Path
import urllib.request
import zipfile

from common import ROOT

URL = "https://buildbot.libretro.com/nightly/windows/x86_64/latest/mgba_libretro.dll.zip"
ARCHIVE_SHA256 = "1bc924e7b20a0cba5e352cbbf75777571b66a4771d61c13eed2bba3569af60fe"
CORE_SHA256 = "6af3783821b69bba6cad654cf73f3e1fceb3b2549dbb933a47ff20ba88f49bfa"
SOURCE_COMMIT = "7a12d6d4b9acb14c0ae62c9166b6a2f3d08007f6"


def verify(path, expected):
    digest = hashlib.sha256(path.read_bytes()).hexdigest()
    if digest != expected:
        raise ValueError(f"Checksum mismatch for {path.name}: {digest}. The optional core is pinned; a newer nightly is not accepted automatically.")


def bootstrap():
    destination = ROOT / "tools/downloads/libretro"
    destination.mkdir(parents=True, exist_ok=True)
    core = destination / "mgba_libretro.dll"
    if core.exists():
        verify(core, CORE_SHA256)
        print(f"Verified optional emulator core: {core}")
        return
    archive = destination / "mgba_libretro.dll.zip"
    if not archive.exists():
        partial = archive.with_suffix(".zip.part")
        print(f"Downloading {URL}", flush=True)
        with urllib.request.urlopen(URL, timeout=30) as response:
            partial.write_bytes(response.read())
        verify(partial, ARCHIVE_SHA256)
        partial.replace(archive)
    verify(archive, ARCHIVE_SHA256)
    with zipfile.ZipFile(archive) as bundle:
        names = bundle.namelist()
        if names != ["mgba_libretro.dll"]:
            raise ValueError("Unexpected emulator archive contents")
        core.write_bytes(bundle.read(names[0]))
    verify(core, CORE_SHA256)
    license_path = destination / "mgba-LICENSE"
    if not license_path.exists():
        license_url = f"https://raw.githubusercontent.com/libretro/mgba/{SOURCE_COMMIT}/LICENSE"
        with urllib.request.urlopen(license_url, timeout=30) as response:
            license_path.write_bytes(response.read())
    print(f"Verified optional emulator core: {core}")


if __name__ == "__main__":
    try:
        bootstrap()
    except (OSError, ValueError, zipfile.BadZipFile) as error:
        raise SystemExit(f"Emulator setup failed: {error}")
