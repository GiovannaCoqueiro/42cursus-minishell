<h1 align=center>
	<b>42cursus</b>
</h1>

<div align=center>
	<h2>
		<i>Minishell</i>
	</h2>
	<img src="https://github.com/GiovannaCoqueiro/42cursus-minishell/assets/115947494/3a8baaa6-f2cf-4f22-8109-944eedff4242" alt=minishell_badge/>
	<p align=center>
    		Inside this repository, you can see all the code that has been created for the Minishell project, including the mandatory part and the incomplete bonus part. The project was done in collaboration with <a href="https://github.com/beatrizdile">Beatriz Dile</a>
	</p>
</div>

---

<div align=center>
	<h2>
		Final score
	</h2>
	<img src="https://github.com/GiovannaCoqueiro/42cursus-minishell/assets/115947494/616c7e93-a227-4022-87ce-183922018a1e" alt=push_swap_grade/>
</div>

---

<h3 align=left>
    Mandatory
</h3>

<p>
	Create a program that works like a shell, following the next conditions.
</p>

<ul>
	<li>Display a prompt when waiting for a new command</li>
	<li>Have a working history</li>
	<li>Search and launch the right executable(using relative path, absolute path or just the the name of the command)</li>
	<li>Handle '</li>
	<li>Handle "</li>
	<li>Implement redirections: '<', '>', '<<', '>>'</li>
	<li>Implemente pipes</li>
	<li>Handle environment variables</li>
	<li>Handle exit status with $?</li>
	<li>Handle signals: 'ctrl-C', 'ctrl-\', 'ctrl-D'</li>
	<li>Implement builtins: 'cd', 'pwd', 'echo', 'exit', 'unset', 'export, 'env'</li>
</ul>

you can run it with:
```sh
  $> ./minishell
```

---

<h3 align=left>
    Bonus
</h3>

| Bonus | Status |
| :---: | :--- |
| Manage \|\| and "&&" with parenthesis | not implemented |
| Manage wildcards | not implemented |
| Manage variables expansion inside ' and " | implemented |

---

<h2>
    Instructions to use
</h2>
Clone this repository in you local computer using a terminal:

```sh
$> git clone git@github.com:GiovannaCoqueiro/42cursus-minishell.git [repository_local]
```

After cloning the project in your local reposiory you can run some commands you can find in Makefile:
<ul>
	<li>$> <b>make all:</b> or just <b>make</b> compiles the project</li>
	<li>$> <b>make clean:</b> deletes the object files created during compilation</li>
	<li>$> <b>make fclean:</b> executes the <b>clean</b> command and also deletes the binary created</li>
	<li>$> <b>make re:</b> executes the <b>fclean</b> command followed by the <b>all</b> command</li>
	<li>$> <b>make bonus:</b> compiles the project</li>
	<li>$> <b>make rebonus:</b> executes the <b>fclean</b> command followed by the <b>rebonus</b> command</li>
	<li>$> <b>make run:</b> executes <b>all</b> and run the program</li>
	<li>$> <b>make val:</b> executes <b>all</b> and run the program with valgrind</li>
</ul>
