# PROG from ../makefile

timeLimit := 1 # s
memLimit  := 64000 # kb

testcaseDir   := Testcase
testResultDir := TestResult

program 	  := ../${PROG}
testResults := $(patsubst ${testcaseDir}/%.input,${testResultDir}/%.log,$(wildcard ${testcaseDir}/*.input))

.PHONY: all clean

all: ${testResults}
	for result in ${testResults}; do \
		ref="${testcaseDir}/$$(basename -s ".log" $${result}).output"; \
		diff $${result} $${ref} > /dev/null; \
		if [ $$? -eq 0 ]; then \
			echo "$${result} pass!"; \
		else \
			echo "$${result} fail!";\
		fi \
	done

${testResults}: testcase = $(patsubst ${testResultDir}/%.log,${testcaseDir}/%.input,$@)
${testResults}: ${testResultDir} ${program}
	ulimit -t ${timeLimit} -v ${memLimit}; \
	${program} < ${testcase} > $@

${testResultDir}:
	mkdir $@

clean:
	rm -r ${testResultDir}
