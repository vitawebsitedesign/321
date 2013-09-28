<!DOCTYPE html>
<html>
	<head>
		<title>Project details</title>
		<meta charset="UTF-8">
		<meta name="description" content="CSCI321 Project details">
		<meta name="keywords" content="csci321 321 Project details">
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
		<h1>Project details</h1>
		<hr/>
		<h1>Iterations</h1>
		<ul>
			<li>#1: Learning Flex &amp; Bison &amp; mingw++</li>
			<li>#2: file format &gt; sql &quot;create table&quot; statements (simple &amp; complex example)</li>
			<li>#3: file format &gt; dtd (simple &amp; complex example)</li>
			<li>#4: file format &gt; xml schema (simple &amp; complex example)</li>
		</ul>
		<h1>Target audience</h1>
		Database designers &amp; developers: replaces their role. The package generates SQL scripts to create a database, and DTD&quot;s &amp; XML Schemas to validate them
		<h1>Requirements</h1>
		<h2>Functional</h2>
		<ul>
			<li>Accurately parse the file format &amp; detect tokens</li>
			<li>Generate expected output after running program (Bison &amp; Flex)</li>
			<li>Error checking for file read &amp; token parsing in Bison</li>
			<li>SQL &quot;create table&quot; scripts, well-formed DTD&quot;s and XML schema&quot;s</li>			
		</ul>					
		<h2>Non-functional</h2>
		<ul>
			<li>Draw database schema</li>
		</ul>					
		<h1>Website concept</h1>
		<i>TBD</i>
	</body>
</html>