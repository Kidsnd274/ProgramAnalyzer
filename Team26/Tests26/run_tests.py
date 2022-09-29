import pathlib
import subprocess
import hashlib


class TestCase:
    def __init__(self, name, folder):
        self.name = name
        self.source_file = folder / (name + "_source.txt")
        self.queries_file = folder / (name + "_queries.txt")
        self.out_file = folder / (name + "_out.xml")


testdir = pathlib.Path(__file__).parent.absolute()
codedir = testdir.parent / "Code26"
outxml = testdir / "out.xml"
logfile = testdir / "run_tests.log"

print(testdir)

# subprocess.Popen("dir", cwd=testdir, shell=True)

# Find autotester executable
locations = [codedir / "cmake-build-debug" / "src" / "autotester" / "Debug" / "autotester.exe",
             codedir / "build" / "src" / "autotester" / "Release" / "autotester.exe",
             codedir / "build" / "src" / "autotester" / "autotester"]

autotester = pathlib.Path()

found = False
for location in locations:
    if location.exists():
        autotester = location
        found = True
        break

if not found:
    print("ERROR: Could not find autotester executable!")
    exit(1)


def cmp_hash(file1, file2):
    hash1 = hashlib.sha256()
    hash2 = hashlib.sha256()

    f1 = open(file1, 'rb')
    while True:
        data1 = f1.read()
        if not data1:
            break
        hash1.update(data1)
    f1.close()

    f2 = open(file2, 'rb')
    while True:
        data2 = f2.read()
        if not data2:
            break
        hash2.update(data2)
    f2.close()

    return hash1 == hash2


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


def run_multiple_tests(tests, milestone_name):
    for testcase in tests:
        print("Running testcase " + testcase.name)
        completed_process = run_test(testcase)
        if completed_process != 0:
            print("ERROR: Testcase " + testcase.name + " in " + milestone_name + " failed to run")
            print("Check run_tests.log!")
            exit(1)
        # if not cmp_hash(outxml, testcase.out_file):
        if not if_passed(outxml):
            print("ERROR: Failed testcase " + testcase.name + " in " + milestone_name)
            print("Check run_tests.log and out.xml!")
            exit(1)


print("-----------------------SPRINT 1-----------------------")
sprint1 = testdir / "sprint1"
tests = [TestCase("test_sprint1", sprint1)]

run_multiple_tests(tests, "Sprint 1")

print("-----------------------MILESTONE 1 / SPRINT 2-----------------------")
milestone1 = testdir / "milestone1"
tests = [TestCase("milestone1_test1", milestone1),
         TestCase("TEST_FOLLOWSSTAR", milestone1),
         TestCase("test_pattern", milestone1),
         TestCase("test_relationship", milestone1)]

run_multiple_tests(tests, "Milestone 1")

print("JOB'S DONE")
