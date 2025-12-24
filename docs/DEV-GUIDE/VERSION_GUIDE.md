# Quick Reference: Version Management

## Where to Change the Version

### Primary Location
**File**: [src/utils.cpp](../src/utils.cpp)  
**Line**: 20

```cpp
const string ver = "0.3";
```

**Change to**:
```cpp
const string ver = "2.0.0";  // or your desired version
```

### Example: Updating from 0.3 to 2.0.0

```bash
# Navigate to source directory
cd /home/techoraye/Documents/metetch

# Edit the file
nano src/utils.cpp
# or
vim src/utils.cpp
# or
code src/utils.cpp  # VS Code
```

Then find line 20 and change:
```
const string ver = "0.3";
↓
const string ver = "2.0.0";
```

### Rebuild After Version Change

```bash
cd build
cmake ..
make clean
make -j$(nproc)

# Verify the new version
./metetch --version
# or look at the display header
./metetch
```

---

## Version Format Guidelines

### Semantic Versioning (Recommended)
Format: `MAJOR.MINOR.PATCH`

Examples:
- `2.0.0` - Major release, breaking changes
- `2.1.0` - Minor release, new features
- `2.1.3` - Patch release, bug fixes

### With Descriptors (Optional)
Add descriptive tags to indicate feature sets:

- `2.0.0-gpu` - GPU monitoring focus
- `2.0.0-metrics` - Enhanced metrics
- `2.0.0+gpu+network` - Multiple features
- `2.0.0-dev` - Development version
- `2.0.0-beta.1` - Beta release

### Example Timeline
```
v0.1.0 ──> v0.3.0 ──> v1.0.0 (stable) ──> v2.0.0 (gpu+metrics)
         (patches)                            ↓
                                         v2.0.1 (bugfix)
                                         v2.1.0 (new features)
```

---

## Files That Reference the Version

While `src/utils.cpp` is the main location, the version string is:

1. **Declared** in: [include/data_types.h](../include/data_types.h)
   ```cpp
   extern const std::string ver;
   ```

2. **Used** in: [src/update.cpp](../src/update.cpp)
   - Compares local version with GitHub latest release

3. **Checked** in: [src/update_handler.cpp](../src/update_handler.cpp)
   - Displays version in update notifications

4. **Displayed** in: [src/render.cpp](../src/render.cpp)
   - May be shown in header (optional)

---

## Version Checking (After Build)

### Method 1: Run with --version flag
```bash
./metetch --version
```

### Method 2: Display output
```bash
./metetch
# Check the banner/header for version string
```

### Method 3: Check source
```bash
grep "const string ver" src/utils.cpp
```

### Method 4: Check binary (using strings)
```bash
strings ./metetch | grep "^[0-9]"
```

---

## Related Global Variables

Located in the same file [src/utils.cpp](../src/utils.cpp):

```cpp
const string ver = "0.3";              // Line 20 - VERSION
const string repo = "techoraye/metfetch";  // GitHub repository
const string api = "https://api.github.com/repos/...";  // Update API
const string bin = "https://github.com/...";  // Download link
```

These are interdependent. If you change the repository name or fork Metetch, you'll also need to update `repo` and `api`.

---

## Version Bump Checklist

When releasing a new version:

- [ ] Update `const string ver` in [src/utils.cpp](../src/utils.cpp)
- [ ] Rebuild: `make clean && make`
- [ ] Test: `./metetch --version`
- [ ] Update [docs/FEATURES_NEW.md](../docs/FEATURES_NEW.md) changelog section
- [ ] Update [README.md](../README.md) if applicable
- [ ] Commit with message: `[Release] v2.0.0`
- [ ] Tag in git: `git tag v2.0.0`
- [ ] Push: `git push origin main --tags`

---

## CMake Integration (Optional)

For advanced projects, you might want to use CMake to manage version:

```cmake
# In CMakeLists.txt
project(metetch VERSION 2.0.0 LANGUAGES CXX)

# Then in source:
#define METETCH_VERSION "2.0.0"
```

But currently, Metetch uses the simple string constant approach.

---

## GitHub Release Integration

The version string is used with the GitHub API to:
1. Check if a newer version exists
2. Download the latest release
3. Notify users of updates

When creating a GitHub release, ensure the tag matches your version:
```
Tag: v2.0.0
Version in code: 2.0.0
```

---

## Quick Commands

```bash
# View current version in source
cat src/utils.cpp | grep "const string ver"

# Change version (Linux sed)
sed -i 's/const string ver = "[^"]*"/const string ver = "2.0.0"/' src/utils.cpp

# Rebuild
cd build && make -j$(nproc)

# Check new version
./metetch | head -1
```

---

**For detailed developer information, see**: [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md)
