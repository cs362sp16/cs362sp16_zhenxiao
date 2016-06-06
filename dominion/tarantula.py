from __future__ import division

import sys
import os
import subprocess

def printc_red(msg):
    '''
    TODO: write comment
    '''
    print '\033[91m' + msg + '\033[0m'

def printc_green(msg):
    '''
    TODO: write comment
    '''
    print '\033[92m' + msg + '\033[0m'

def printc_yellow(msg):
    '''
    TODO: write comment
    '''
    print '\033[93m' + msg + '\033[0m'

def count_lines(fname):
    '''
    counts number of lines in given file
    @param fname file name
    @return: number of lines in file
    '''
    return len(open(fname, 'r').readlines())

def count_digits(n):
    '''
    count decimal digits in given number
    @param n number
    @return: decimal digits in number
    '''
    count = 0
    while n != 0:
        count += 1
        n = n // 10
    return count

def get_result(msg):
    '''
    returns if given test result message means test passed or not
    @precondition: unit test uses Verify362 macro to check if test passed
    @param msg test result message
    @return: true if and only if test result message means test passed
    '''
    return not msg.startswith('Verify362')

def suspiciousness(passed, failed, totalpassed, totalfailed):
    '''
    returns suspiciousness of given coverage unit
    @precondition: passed != 0 or failed != 0
    @param passed number of passed tests that execute coverage unit
    @param failed number of failed tests that execute coverage unit
    @param totalpassed total number of tests passed
    @param totalfailed total number of tests failed
    @return: suspiciousness of coverage unit
    '''
    numerator = failed / totalfailed
    denominator = passed / totalpassed + numerator
    return numerator / denominator

def main():
    '''
    TODO: comment
    '''
    maxtests = 4
    # define test suite
    unittests = ['unittest' + str(i) for i in range(1, maxtests + 1)]
    cardtests = ['cardtest' + str(i) for i in range(1, maxtests + 1)]
    testsuite = unittests + cardtests
    # define source file
    source_file = 'dominion.c'
    count = count_lines(source_file)
    passed = [0 for i in range(count + 1)]
    failed = [0 for i in range(count + 1)]
    totalpassed = 0
    totalfailed = 0
    # run test suite and record results
    for test in testsuite:
        subprocess.call(['make', 'clean'])
        subprocess.call(['make', test])
        try:
            tmp = subprocess.check_output(['./' + test], stderr=subprocess.STDOUT)
        except subprocess.CalledProcessError as e:
            tmp = e.output
        # record test result
        result = get_result(tmp)
        if (result):
            totalpassed += 1
        else:
            totalfailed += 1
        subprocess.call(['gcov', source_file])
        for line in open(source_file + '.gcov', 'r').readlines():
            tmp = line.split(':')
            num = tmp[0].lstrip()
            i = int(tmp[1])
            if num.startswith('-') or num.startswith('#') or num.startswith('='):
                continue
            elif result:
                passed[i] += 1
            else:
                failed[i] += 1
    width = count_digits(count)
    i = 1
    for line in open(source_file, 'r').readlines():
        msg = str(i).rjust(width) + ':' + line[:-1]
        if passed[i] > 0 or failed[i] > 0:
            tmp = suspiciousness(passed[i], failed[i], totalpassed, totalfailed)
            if tmp == 0:
                printc_green(msg)
            elif tmp <= 0.5:
                printc_yellow(msg)
            else:
                printc_red(msg)
        else:
            print msg
        i += 1

if __name__ == '__main__':
    main()