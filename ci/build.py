import os
import re
import shutil

COLOR_ESC = '\033['
COLOR_RESET = f'{COLOR_ESC}0m'
COLOR_GREEN = f'{COLOR_ESC}32m'
COLOR_RED = f'{COLOR_ESC}31m'
COLOR_CYAN = f'{COLOR_ESC}36m'
COLOR_GRAY = f'{COLOR_ESC}30;1m'

PLATFORMS = ["esp32dev", "esp01", "esp12e", "wemos_d1_mini_lite"]


def prepare() -> None:
    print(f"🡢 {COLOR_CYAN}Preparation{COLOR_RESET}")

    print(f"  🡢 {COLOR_GRAY}Backing up platformio.ini{COLOR_RESET}")
    shutil.copy("./platformio.ini", "platformio.ini.bak")

    print(f"  🡢 {COLOR_GRAY}Copying over build/platformio.ini{COLOR_RESET}")
    shutil.copy("./ci/platformio.ini", "platformio.ini")

    if os.path.exists("./build"):
        print(f"  🡢 {COLOR_GRAY}Removing existing build folder...{COLOR_RESET}")
        shutil.rmtree("./build")

    print(f"  🡢 {COLOR_GRAY}Creating build folder...{COLOR_RESET}")
    os.mkdir("./build")

    print(f"  🡢 {COLOR_GREEN}Success!{COLOR_RESET}")


def cleanup() -> None:
    print(f"🡢 {COLOR_CYAN}Cleanup{COLOR_RESET}")

    print(f"  🡢 {COLOR_GRAY}Restoring platformio.ini...{COLOR_RESET}")
    shutil.copy("platformio.ini.bak", "platformio.ini")

    print(f"  🡢 {COLOR_GRAY}Removing platformio.ini.bak...{COLOR_RESET}")
    os.remove("platformio.ini.bak")

    print(f"  🡢 {COLOR_GREEN}Success!{COLOR_RESET}")


def build() -> int:
    print(f"🡢 {COLOR_CYAN}Build{COLOR_RESET}")

    error_has_occurred = False
    code = 0

    for platform in PLATFORMS:
        print(f"::group::Build {platform}")
        print(f"  🡢 {COLOR_CYAN}Building for {platform}{COLOR_RESET}")

        if build_for_platform(platform) == 0:
            print(f"    🡢 {COLOR_GREEN}Success!{COLOR_RESET}")
        else:
            error_has_occurred = True
            print(f"    🡢 {COLOR_RED}Failed!{COLOR_RESET}")

        print(f"::endgroup::")

    if error_has_occurred:
        print(f"  🡢 {COLOR_RED}Failed!{COLOR_RESET}")
        code = 1
    else:
        print(f"  🡢 {COLOR_GREEN}Success!{COLOR_RESET}")

    return code


def build_for_platform(platform: str) -> int:
    shutil.copy("src/defines.h", "src/defines.h.bak")
    board = "BOARD_"

    if platform == "esp12e":
        board += "SLIMEVR"
    elif platform == "wemos_d1_mini_lite":
        board += "WEMOSD1MINI"
    elif platform == "esp01":
        board += "ESP01"
    elif platform == "esp32dev":
        board += "WROOM32"
    else:
        raise Exception("Unknown platform")

    with open("src/defines.h", "r") as f:
        lines = f.read().rstrip().lstrip()
        lines = re.sub("#define BOARD .*", f"#define BOARD {board}", lines)

        with open("src/defines.h", "wt") as f:
            f.write(lines)

    print("Building for platform: " + platform)
    ret_code = os.system(f"platformio run -e {platform}")

    if ret_code == 0:
        print("Build succeeded")

        shutil.copy(f".pio/build/{platform}/firmware.bin",
                    f"build/{platform}.bin")
    else:
        print("Build failed")

    shutil.copy("src/defines.h.bak", "src/defines.h")
    os.remove("src/defines.h.bak")

    return ret_code


def main() -> None:
    prepare()
    code = build()
    cleanup()

    os._exit(code)


if __name__ == "__main__":
    main()
