# Vendored Third-Party Code

This repository vendors copies of two upstream projects under `third_party/`,
along with one git submodule. Both `astu` and `astu-box2d` are no longer
actively maintained upstream; we vendor them so we can apply local fixes
(CMake modernization, portable SDL2 detection, etc.). Erin Catto's `box2d` is
still actively maintained, so it is kept as a git submodule pinned to a
specific commit.

## `third_party/astu`

- Upstream: <https://github.com/divotkey/astu>
- Vendored at commit: `520afe5c5ee82b2f52c3c219db98f76d798f4bb3`
- License: not present in upstream tree at vendored revision; see upstream
  repository for any later license additions.

### Local patches
- `CMakeLists.txt`: bumped `cmake_minimum_required` from `3.1` to
  `3.10...3.30`.
- `CMakeLists.txt`: replaced the per-OS hardcoded SDL2 lookup with a
  portable detection chain: `find_package(SDL2 CONFIG)` →
  `pkg_check_modules(sdl2)` → macOS framework fallback → Windows
  `SDL2_HOME` fallback → fatal error.

## `third_party/astu-box2d`

- Upstream: <https://github.com/divotkey/astu-box2d>
- Vendored at commit: `0657accc7819e90e610cf923bfc42c4141e03faa`
- License: see `third_party/astu-box2d/LICENSE`.

### Local patches
- `CMakeLists.txt`: bumped `cmake_minimum_required` from `3.1` to
  `3.10...3.30`.
- The original repository's nested `box2d` submodule was removed in favor
  of a top-level submodule of this repository (see below).

## `third_party/astu-box2d/box2d` (submodule)

- Upstream: <https://github.com/erincatto/box2d>
- Pinned at commit: `cd2c28dba83e4f359d08aeb7b70afd9e35e39eda`
  (tag `v2.4.1-3-gcd2c28d`)
- License: see `third_party/astu-box2d/box2d/LICENSE`.

This is a regular git submodule of *this* repository (registered in
`.gitmodules`). To bump it later:

```sh
git -C third_party/astu-box2d/box2d fetch
git -C third_party/astu-box2d/box2d checkout <new-sha>
git add third_party/astu-box2d/box2d
git commit -m "Bump box2d to <new-sha>"
```
