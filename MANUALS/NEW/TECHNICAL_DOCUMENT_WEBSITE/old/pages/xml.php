<!DOCTYPE html>
<html>
	<head>
		<title>XML tutorial</title>
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
		<h1>XML tutorial</h1>
		<hr/>
		<article>
			<h2>What is xml</h2>
			Used to describe objects. e.g.
			<pre>
				&lt;person&gt;
					&lt;name&gt;eric&lt;/name&gt;
					&lt;age&gt;21&lt;/age&gt;
				&lt;/person&gt;
			</pre>
			<div class="next-section-div">lets learn xml!</div>
		</article>
		<article>
			<h2>How to code xml</h2>
			The stuff inside brackets is a "element". e.g. <pre>&lt;person&gt;&lt;/person&gt;</pre> is a element
			
			---ELEMENT
			You can put elements inside elements. e.g.
			<pre>
				&lt;person&gt;
					<b>&lt;age&gt;&lt;/age&gt;</b>
				&lt;/person&gt;
			</pre>
			
			can have values. e.g.
			<pre>
				&lt;person&gt;
					&lt;age&gt;<b>21</b>&lt;/age&gt;
				&lt;/person&gt;
			</pre>
			
			but.. can only have 1 <b>root</b>(outside) element. e.g.
			<pre>
				&lt;person&gt;
					&lt;age&gt;&lt;/age&gt;
				&lt;/person&gt;
			</pre>
			
			GOOD! but...
			
			<pre>
				&lt;person&gt;
					&lt;age&gt;&lt;/age&gt;
				&lt;/person&gt;
				<b>
				&lt;another-person&gt;
					&lt;age>&lt;/age&gt;
				&lt;/another-person&gt;
				</b>
			</pre>
			
			bad. below is good:
			
			<pre>
				<b>&lt;persons&gt;&lt;/b&gt;
					&lt;person&gt;
					&lt;/person&gt;
					&lt;person&gt;
					&lt;/person&gt;
				<b>&lt;/persons&gt;</b>
			</pre>
			
			---TELL COMPUTER ITS A .XML FILE, NOT A .TXT FILE
			put <pre>&lt;?xml version="1.0" ?&gt;</pre> at top. e.g.
			
			<pre>
				&lt;?xml version="1.0" ?&gt;
				&lt;person&gt;
					&lt;age&gt;21&lt;/age&gt;
				&lt;/person&gt;
			</pre>
			
			<a href="http://www.xmlvalidation.com/">this website can check if your xml is good</a>
			<div class="next-section-div">xml looks stupid. why need it?</div>
		</article>
		<article>
			<h2>Reason for xml</h2>
			a text file:
			<pre>
				i am a chinese, international student
			</pre>
			
			a person can read that, but how can computer read that? 
			if computer want to find out what country a student is from, or if they are an international student, how?
			this is why "elements" are used, instead of english sentence. e.g.
			
			<pre>
				&lt;student&gt;
					&lt;country&gt;chinese&lt;/country&gt;
					&lt;type&gt;international&lt;/type&gt;
				&lt;/student&gt;
			</pre>
			
			now computer can read it! 
		</article>
	</body>
</html>
