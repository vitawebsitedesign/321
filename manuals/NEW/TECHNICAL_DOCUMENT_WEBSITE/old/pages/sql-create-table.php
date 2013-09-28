<!DOCTYPE html>
<html>
	<head>
		<title>SQL create table tutorial</title>
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
		<h1>SQL tutorial</h1>
		<hr/>
		<article>
			<h2>SQL tutorial</h2>
			a table:
			
			<img src="../img/excel-table.jpg" alt="excel table"/>
			
			in monitor, it looks like that. in computer hard drive, thats not how it looks. 
			instead.. its text! we call this &quot;text to create tables&quot; <b>SQL</b>
			
			to create the same table in SQL, its:
			
			<pre>
				<div class="heading-code">mySQL.sql</div>
				CREATE TABLE myTable (
					
				);
			</pre>
			
			<b>myTable</b> is the table name. Lets put stuff in it:
			
			<pre>
				<div class="heading-code">mySQL.sql</div>
				CREATE TABLE myTable (
					<b>
					personName VARCHAR(50),
					projectName VARCHAR(50)	
					</b>
				);
			</pre>
			
			VARCHAR is string
		</article>
	</body>
</html>
