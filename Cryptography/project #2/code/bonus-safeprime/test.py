import os
import subprocess

if __name__ == '__main__':
    # current directory
    directory = os.path.dirname(os.path.abspath(__file__))
    # path to subscript
    path = os.path.join(directory, 'safeprimegen.py')

    hits, false_positives, ideals, tests, timeframe = 0, 0, 0, 100, 5 * 60
    for _ in range(tests):
        try:
            result = subprocess.run(['python', path], timeout=timeframe, text=True)
            hits += 1
            if result.returncode > 0:
                ideals += 1
            if result.returncode < 0:
                false_positives += 1
        except subprocess.TimeoutExpired:
            continue
    print(
        f'''Results for {tests} {timeframe // 60}-minute tests:
    >>> Hit ratio: {hits}/{tests}
    >>> Overall success: {(hits * 100 / tests):.2f}%
    >>> Ideal hits: {ideals}/{tests} (~{(ideals * 100 / tests):.2f}%)
    >>> False positives: {false_positives}/{tests} (~{(false_positives * 100 / tests):.2f}%)'''
    )
