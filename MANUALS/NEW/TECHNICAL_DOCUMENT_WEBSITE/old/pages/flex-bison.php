<!DOCTYPE html>
<html>
	<head>
		<title>Flex tutorial</title>
		<meta charset="UTF-8">
		<meta name="description" content="Flex tutorial for beginners - Learn Adobe Flex programming in simple and easy steps starting with Flex Environment Setup, Web Application Creation, Deploy and Debug Application, Style with CSS, Skin, Flex Components, Basic, Form and Complex Controls,  Layout Panels, Event Handling, Event Bubbling,  Custom Controls, RPC Services, FlexUnit Integration, Internationalization, Printing Support.">
		<meta name="keywords" content="Adobe, Flex, Environment, Setup, Web, Application, Deploy, Debug, Application, Style, CSS, Skin, Component, Model, Basic, Form, Complex, Controls, Layout, Panels, Event, Handling, Bubbling, Custom, RPC, Services, FlexUnit Integration, Internationalization, Printing, Support">
		<script src="http://code.jquery.com/jquery-latest.min.js"></script>
		<script src="../scripts/article-slideshow.js"></script>
		<link rel="stylesheet" type="text/css" href="../styles/main.css">
	</head>
	<body>
		<header>
			<nav>
				<ul>
					<?php include_once('../scripts/fetchNav.php'); ?>
				</ul>
			</nav>
		</header>	
		<h1>Flex tutorial</h1>
		<hr/>
		<article>
			<h2>What flex does</h2>
			Changes text. example:
			<pre>
				I like cake
			</pre>
			to
			<pre>
				I like apple
			</pre>
			<div class="next-section-div">Show me the Flex code!</div>
		</article>
		<article>
			<h2>Flex code</h2>
			Looks messy, has 3 sections:
			<ul>
				<li>First section is between <span class="inline-code">%{</span> and <span class="inline-code">%}</span>. Has C++ stuff</li>
				<li>Second section is between <span class="inline-code">%%</span> and <span class="inline-code">%%</span>. Has Flex stuff. Each line tells flex what to match, and what happens when matched</li>
				<li>Third section is C++ code</li>
			</ul>
			<pre>
				<div class="heading-code">myFlex.l</div>				
				%{
				
				#include &lt;iostream&gt;
				using namespace std;
				#define YY_DECL extern &quot;C&quot; int yylex()
				
				%}
				%%
				
				cake  { cout << &quot;apple&quot;; }
				
				%%
				
				int main() {
				    yylex();
				}		
			</pre>
			<div class="next-section-div">Lets compile this program!</div>
		</article>
		<article>
			<h2>Compile and run flex</h2>
			<pre>
				<div class="heading-code">banshee terminal</div>
				flex myFlex.l
				g++ -ll lex.yy.c
				./a.out				
				
				> i like cake
				i like <span class="highlight">apple</span>
			</pre>
		</article>
	</body>
</html>