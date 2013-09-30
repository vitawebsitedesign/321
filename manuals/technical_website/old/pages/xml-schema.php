<!DOCTYPE html>
<html>
	<head>
		<title>XML Schema tutorial</title>
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
		<h1>XML Schema tutorial</h1>
		<hr/>
		<article>
			<h2>What is XML Schema?</h2>
			XML Schema = DTD, hard mode
			It does the same thing, but more powerful. BUT.. very difficult to learn
			
			<div class="next-section-div">ok... show me the code :S</div>
		</article>
		<article>
			<h2>XML Schema code</h2>
			A normal XML file:
			
			Instead of a DTD, heres a XML schema:
			
			<pre>
				&lt;?xml version="1.0"?&gt;
				&lt;xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema"&gt;
			
				&lt;xsd:element name="person"&gt;
					&lt;xsd:complexType&gt;
						&lt;xsd:sequence&gt;
							&lt;xsd:element name="age" type="xsd:string"/&gt;
						&lt;/xsd:sequence&gt;
					&lt;/xsd:complexType&gt;
				&lt;/xsd:element&gt;
			
				&lt;/xsd:schema&gt;
			</pre>
			
			It looks messy, because it doesn't look like C++ or Java, very different
			<div class="next-section-div">teach me!</div>
		</article>
		<article>
			<h2>XML Schema code</h2>
			<pre>
				&lt;?xml version="1.0"?&gt;
				&lt;xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema"&gt;
			
				&lt;xsd:element name="person"&gt;
					&lt;xsd:complexType&gt;
						&lt;xsd:sequence&gt;
							&lt;xsd:element name="age" type="xsd:string"/&gt;
						&lt;/xsd:sequence&gt;
					&lt;/xsd:complexType&gt;
				&lt;/xsd:element&gt;
			
				&lt;/xsd:schema&gt;
			</pre>
			
			---explanation
			
			<ul>
				<li>A XML Schema file is a XML file, so you need to tell the computer that its a XML file, not a .txt file. <pre>&lt;?xml version="1.0"?&gt;</pre></li>
				<li>The 2nd line can just be memorised</li>
				<li>You don&#39;t need to know what <b>xsd:</b> does, just memorise it</li>
				<li><b>element</b> says &quot;the XML file has an element</li>
				<li><b>complexType</b> says that this element (in this case, <i>person</i>), contains a sequence (see below)</li>
				<li><b>sequence</b> means &quot;set of elements&quot; in English. It means that this &quot;element&quot;, has an element inside of it</li>
			</ul>
			
			a confusing programming language, email me if you need any help.
		</article>
	</body>
</html>
