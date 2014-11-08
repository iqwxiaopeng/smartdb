# Smartdb

## How to run test cases

### Getting Google Test

Download the latest [Google Test](https://code.google.com/p/googletest/downloads/list) source
and unzip it in `contrib/gtest` directory.

```bash
$ ls contrib/gtest/
CHANGES        CONTRIBUTORS   Makefile.am    README         build-aux      codegear       configure.ac   include        make           samples        src            xcode
CMakeLists.txt LICENSE        Makefile.in    aclocal.m4     cmake          configure      fused-src      m4             msvc           scripts        test
```

### Running via shell

```bash
$ cd test
$ ./build.sh
$ ./run_gtest
```

### Running in Eclipse CDT

1. Get "C/C++ Unit Test" plugin.
    1. Help -> Install New Software.
    2. Work with: "CDT".
    3. Check "C/C++ Unit Testing Support" in "CDT Optional Features".
    4. Install it.

    ![Get "C/C++ Unit Test" plugin](doc/img/eclipse/installing_unit_test_support.png)
2. Make build configuration to create `test/run_gtest` binary.
    1. Project -> Properties -> C/C++ Build -> Manage Configurations ...
    2. Create a configuration named "gtest".
    3. Return to "C/C++ Build" dialogue.
    4. Build command: `${workspace_loc:/smartdb}/test/build.sh`, build directory: `${workspace_loc:/smartdb}/test/`.

    ![Make build configuration to create `test/run_gtest` binary](doc/img/eclipse/gtest_build_config.png)
3. Create configuration to build & run `test/run_gtest` binary.
    1. Run -> Run Configurations -> C/C++ Unit.
    2. C/C++ Application: `${workspace_loc:/smartdb}/test/run_test`.
    3. Build configuration: "gtest".
    4. Apply.

    ![Create configuration to build & run `test/run_gtest` binary](doc/img/eclipse/gtest_run_config.png)
4. Run unit test.
    1. Open "C/C++ Unit" view.
    2. Click "Rerun All Tests" button.

    ![Run unit test](doc/img/eclipse/unit_test_view.png)
