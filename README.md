# Pipex

## Introduction
Pipex is a project from 42 School that recreates the behavior of shell piping (\`|\`). It takes an input file, processes two commands through a pipe, and writes the output to a specified file.

## How It Works
The program mimics the shell command:
\`\`\`
< infile cmd1 | cmd2 > outfile
\`\`\`
which means:
1. Reads from \`infile\`
2. Executes \`cmd1\`, sending its output to a pipe
3. Passes the output of \`cmd1\` as input to \`cmd2\`
4. Writes the final output to \`outfile\`

## Compilation
Compile the program using:
\`\`\`bash
make
\`\`\`

## Usage
Run Pipex with:
\`\`\`bash
./pipex infile "cmd1" "cmd2" outfile
\`\`\`
Example:
\`\`\`bash
./pipex input.txt "grep hello" "wc -l" output.txt
\`\`\`
This will:
- Read from \`input.txt\`
- Find lines containing "hello"
- Count the number of matching lines
- Write the result to \`output.txt\`

## Error Handling
- If the input file does not exist or cannot be read, Pipex redirects it to \`/dev/null\`
- If a command is not found, it prints an error message
- If \`outfile\` cannot be created, it displays an error and exits

## System Calls Used
- \`open()\` → Opens input and output files
- \`pipe()\` → Creates a pipe for inter-process communication
- \`fork()\` → Creates child processes to run commands
- \`dup2()\` → Redirects input and output for commands
- \`execve()\` → Executes commands
- \`waitpid()\` → Waits for child processes to finish

## Notes
- This implementation only handles two commands.
- Paths are extracted from the \`PATH\` environment variable.
- The program ensures resource management (closing pipes, files).

## Author
Made with ❤️ by [Your Name]
EOF
