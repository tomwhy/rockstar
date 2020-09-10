import os
import subprocess
from typing import List, Tuple
import itertools


class TestResult:
    def __init__(self, diff: List[Tuple[str, str]]):
        self._msg = ""
        for out, expected in diff:
            if out and expected:
                self._msg += "expected {} but got {}\n".format(expected, out)
            elif not out and expected:
                self._msg += "Missing expected line: {}\n".format(expected)
            elif out and not expected:
                self._msg += "got unexpected line: {}\n".format(out)
        self._msg = self._msg[:-1]

    @property
    def success(self) -> bool:
        return not bool(self._msg)

    @property
    def msg(self) -> str:
        return self._msg


class Test:
    def __init__(self, interpeter: str, test_file: str, output_file: str, input_file: str):
        if not os.path.exists(test_file):
            raise RuntimeError(
                "Test file {} does not exists".format(test_file))

        if not os.path.exists(output_file):
            raise RuntimeError(
                "output file {} does not exists".format(output_file))

        self._cmd = '"{}" "{}"'.format(interpeter, test_file)
        self._expected_output = output_file
        if os.path.exists(input_file):
            self._cmd += ' < "{}"'.format(input_file)

    def test(self) -> TestResult:
        diff = []

        res = subprocess.run(self._cmd, stdout=subprocess.PIPE,
                             stderr=subprocess.STDOUT, text=True)
        with open(self._expected_output) as file:
            for out, expected in itertools.zip_longest(res.stdout.splitlines(), file, fillvalue=str()):
                expected = expected.replace("\n", "")
                if out != expected:
                    diff.append((out, expected))

        return TestResult(diff)
