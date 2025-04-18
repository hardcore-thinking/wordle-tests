# Test exercise - Wordle

## Table of contents

+ [Test part](#test-part)
    + [How to run the project](#how-to-run-the-project)
    + [Install the dependencies](#install-the-dependencies)
    + [Run the tests](#run-the-tests)
    + [Run the actual project](#run-the-actual-project) 
+ [Coverage part](#coverage-part)

## Test part

### How to run the project

If it's not already the case, please install [Xmake](https://xmake.io/#/getting_started?id=installation) as it's necessary to first install the dependencies then run the tests and the project itself.

### Install the dependencies

To install the dependencies, simply run the following command at the root of the project directory :

```
xmake build -y
```

### Run the tests

```
xmake test -v
```

### Run the actual project

```
xmake run
```

## Coverage part

To take a look at the code coverage, you can use [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage/releases/tag/release-0.9.9.0) on Windows (need to be installed) to get coverage statistics. Simply run the following command (assuming we're in `C:\Users\user\Wordle`) :

```
opencppcoverage --sources C:\Users\user\Wordle -- build\windows\x64\debug\WordleGame.exe
```

Then look at the results in the resulting directory named like this `CoverageReport-YYYY-MM-DD-HHhMMmSSs` and open `index.html` in your web browser.

**OR**

You can use GCOV to get those statistics. Then use the command as follows :

```
gcov -rHa ./build/.objs/WordleGame/<your-platform>/<your-architecture>/release/src/*.gcno
```

For example :

```
gcov -rHa ./build/.objs/WordleGame/linux/x86_64/release/src/*.gcno
```