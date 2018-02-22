package main

/**
 * @author BinhNt42
 * @brief Parser clang-tidy output
 */
import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"os"
	"strings"
)

type Args struct {
	FileInput    string
	Exclude      string
	StartPattern string
}

func (args *Args) Parse() {
	flag.StringVar(&args.FileInput, "input", "", "Input file")
	flag.StringVar(&args.Exclude, "exclude", "", "Exclude pattern: googletest,_test")
	flag.StringVar(&args.StartPattern, "start-pattern", "/", "Pattern for detect start a record")
	flag.Parse()
}

type Exclude struct {
	Pattern []string
}

func (ex *Exclude) IsMatched(str string) bool {
	if len(ex.Pattern) == 0 {
		return false
	}
	for _, pattern := range ex.Pattern {
		if strings.Index(str, pattern) != -1 {
			return true
		}
	}
	return false
}

func main() {
	args := Args{}
	args.Parse()

	exclude := Exclude{}
	if len(args.Exclude) > 0 {
		exclude.Pattern = strings.Split(args.Exclude, ",")
	}

	file, err := os.Open(args.FileInput)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	ignore := false
	for scanner.Scan() {
		line := scanner.Text()
		if strings.Index(line, args.StartPattern) == 0 {
			if exclude.IsMatched(line) {
				// ignore lines
				ignore = true
			} else {
				ignore = false
			}
		}
		if !ignore {
			fmt.Println(line)
		}
	}
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
