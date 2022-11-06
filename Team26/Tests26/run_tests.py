import pathlib
import subprocess
import hashlib
import sys
import os

testdir = pathlib.Path(__file__).parent.absolute()
codedir = testdir.parent / "Code26"
outxml = testdir / "out.xml"
logfile = testdir / "run_tests.log"


class TestCase:
    def __init__(self, name, folder):
        self.name = name
        self.source_file = folder / (name + "_source.txt")
        self.queries_file = folder / (name + "_queries.txt")
        self.out_file_failed = (name + "_out.xml")
        self.log_file_failed = (name + ".log")


print(testdir)

# Find autotester executable
locations_windows = [codedir / "cmake-build-debug" / "src" / "autotester" / "Debug" / "autotester.exe",
                     codedir / "build" / "src" / "autotester" / "Release" / "autotester.exe"]

locations_mac = [codedir / "cmake-build-debug" / "src" / "autotester" / "autotester",
                 testdir.parent.parent.parent / "build" / "src" / "autotester" / "autotester"]

autotester = pathlib.Path()

found = False

if sys.platform == 'win32':
    for location in locations_windows:
        if location.exists():
            autotester = location
            found = True
            break
elif sys.platform == 'darwin':
    for location in locations_mac:
        if os.path.isfile(location) and os.access(location, os.X_OK):
            autotester = location
            found = True
            break

if not found:
    print("ERROR: Could not find autotester executable!")
    exit(1)


def move_file(curr_file, new_location):
    if new_location.exists():
        new_location.unlink()
    curr_file.rename(new_location)


def move_failed_files(testcase, out_file_also):
    if not ((testdir / "failed_tests").exists and (testdir / "failed_tests").is_dir()):
        pathlib.Path.mkdir(testdir / "failed_tests")
    move_file(logfile, testdir / "failed_tests" / testcase.log_file_failed)
    if out_file_also:
        move_file(outxml, testdir / "failed_tests" / testcase.out_file_failed)


def move_passed_files(testcase):
    if not ((testdir / "passed_tests").exists and (testdir / "passed_tests").is_dir()):
        pathlib.Path.mkdir(testdir / "passed_tests")
    move_file(logfile, testdir / "passed_tests" / testcase.log_file_failed)
    move_file(outxml, testdir / "passed_tests" / testcase.out_file_failed)


def if_passed(result):
    with open(result) as f:
        if 'failed' in f.read():
            return False
    return True


def run_test(testcase):
    f = open(logfile, "w")
    source_file = testcase.source_file.resolve()
    queries_file = testcase.queries_file.resolve()
    args = [autotester.resolve(), source_file, queries_file, outxml.resolve()]
    process = subprocess.Popen(args, stdout=f)
    process.communicate()
    f.close()
    return process.returncode


failed_tests = []


def run_multiple_tests(selected_tests):
    for testcase in selected_tests:
        print("Running testcase " + testcase.name + "...", end="")
        completed_process = run_test(testcase)
        if completed_process != 0:
            failed_tests.append(testcase)
            move_failed_files(testcase, False)
            print(" X Failed to run")
        elif not if_passed(outxml):
            failed_tests.append(testcase)
            move_failed_files(testcase, True)
            print(" X Failed testcase.")
        else:
            move_passed_files(testcase)
            print(" PASSED")


# Edit test cases here
print("-----------------------SPRINT 1-----------------------")
sprint1 = testdir / "sprint1"
tests = [TestCase("test_sprint1", sprint1)]

run_multiple_tests(tests)

print("-----------------------MILESTONE 1 / SPRINT 2-----------------------")
milestone1 = testdir / "milestone1"
tests = [TestCase("milestone1_test1", milestone1),
         TestCase("TEST_FOLLOWSSTAR", milestone1),
         TestCase("test_pattern", milestone1),
         TestCase("test_relationship", milestone1)]

run_multiple_tests(tests)


print("-----------------------SPRINT 3 / DEMO 2-----------------------")
demo2 = testdir / "demo2"
tests = [TestCase("test_calls", demo2),
         # TestCase("test_pattern2", demo2), # Test case broken
         ]

run_multiple_tests(tests)


print("-----------------------SPRINT 4 / MILESTONE 2-----------------------")
milestone2 = testdir / "milestone2"
tests = [TestCase("milestone2_test1", milestone2)]

run_multiple_tests(tests)

print("-----------------------SPRINT 5 / MILESTONE 3-----------------------")
milestone3 = testdir / "milestone3"
tests = [TestCase("milestone3_test1", milestone3),
         TestCase("milestone3_test2", milestone3),
         TestCase("milestone3_test3", milestone3),
         TestCase("affectstest", milestone3)]

run_multiple_tests(tests)

print("")
if failed_tests:
    with open("failed_tests.txt", "w") as f:
        for cases in failed_tests:
            f.write(cases.name)
            f.write("\n")
    print("Test cases failed X Check failed_tests.txt for the list and failed_tests folder for log and out.xml")
    exit(1)
else:
    print("JOB'S DONE!")
