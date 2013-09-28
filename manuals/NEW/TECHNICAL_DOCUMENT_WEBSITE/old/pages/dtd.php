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
		<h1>DTD</h1>
		<hr/>
		<article>
			<h2>What it looks like</h2>
			looks like:
			<pre>
				&lt;?xml version="1.0" ?&gt;
				<b>
				&lt;!DOCTYPE person [
					&lt;!ELEMENT person (age)&gt;
					&lt;!ELEMENT age (&#35;PCDATA)&gt;
				]>
				</b>
			
				&lt;person&gt;
					&lt;age&gt;21&lt;/age&gt;
				&lt;/person&gt;
			</pre>
			<div class="next-section-div">i dont care about dtd! why need it?</div>
		</article>
		<article>
			<h2>Why dtd</h2>
			A xml file is cool. but what if... you made a MISTAKE? e.g.
			
			<pre>
				&lt;?xml version="1.0" ?&gt;
				&lt;person&gt;
					&lt;age&gt;21&lt;/age&gt;
					&lt;racecar-flying-speed&gt;100000&lt;/racecar-flying-speed&gt;
				</person>
			</pre>
			
			a person has an &quot;age&quot;, but not a &quot;racecar flying speed&quot;! :S
			can use DTD to see if we did something stupid (you will see later) in XML
			so... DTD is like a compiler for XML
	
			<div class="next-section-div">tell me how to code DTD!</div>
		</article>
		<article>
			<h2>How to code dtd</h2>
			We do this slow. 
			Below is a xml file we are going to validate (<i>make sure no errors</i>):
			
			<pre>
				<div class="header-code">myXML.xml</div>
				&lt;?xml version="1.0" ?&gt;
				&lt;person&gt;
					&lt;age&gt;21&lt;/age&gt;
				&lt;/person&gt;
			</pre>
			
			Now lets do DTD code. 
			Tell computer what is inside the root, <b>person</b>:
			<pre>
				<div class="header-code">myDTD.dtd</div>
				&lt;!ELEMENT person (age)&gt;
				&lt;!ELEMENT age (&#35;PCDATA)&gt;	
			</pre>
			stuff inside brackets says whats inside the element
			<pre>&lt;!ELEMENT person (age)&gt;</pre> means that &quot;person&quot; has an element &quot;age&quot;
			<b>!ELEMENT</b> means a element. 
			C++ has data-types INT, FLOAT, CHAR. DTD has only 1 - &#35;PCDATA, which means anything
			
			The 2 files are finished! Now lets tell the XML file to use the DTD file:
			<pre>
				<div class="header-code">myXML.xml</div>
				&lt;?xml version="1.0" ?&gt;
				<b>&lt;!DOCTYPE person SYSTEM "myDTD.dtd"&gt;</b>
				&lt;person&gt;
					&lt;age&gt;21&lt;/age&gt;
				&lt;/person&gt;
			</pre>
			
			That line is hard to explain, so just memorise it.
			It says that there is a DTD(DOCTYPE) for element &quot;person&quot;, which is on the &quot;SYSTEM&quot; hard drive, and its called &quot;myDTD.dtd&quot;
			
			<div class="next-section-div">what if a person has 2 age&#39;s? the DTD above says a person only has 1 age!</div>
		</article>
		<article>
			<h2>Quantifiers</h2>
			look:
			
			<pre>
				<div class="header-code">myXML.xml</div>
				&lt;?xml version="1.0" ?&gt;
				&lt;!DOCTYPE person SYSTEM "myDTD.dtd"&gt;
				&lt;person&gt;
					&lt;age&gt;&lt;/age&gt;
					&lt;age&gt;&lt;/age&gt;
				&lt;/person&gt;
			</pre>
			
			<pre>
				<div class="header-code">myDTD.dtd</div>
				&lt;!ELEMENT person (age)&gt;
				&lt;!ELEMENT age (&#35;PCDATA)&gt;
			</pre>
			
			See something wrong?
			
			<pre>
				<div class="header-code">myDTD.dtd</div>
				&lt;!ELEMENT person (<b>age</b>)&gt;
				&lt;!ELEMENT age (&#35;PCDATA)&gt;
			</pre>
			
			<ul>
				<li>nothing after element name, means exactly 1</li>
				<li>? means 0 or 1</li>
				<li>* means 0 or more</li>
				<li>+ means 1 or more</li>
			</ul>
			
			The DTD says that &quot;person&quot; can only have 1 age, or else validator/compiler error
			DTD below says that the XML file can have more than 1 age:
			
			<pre>
				<div class="header-code">myDTD.dtd</div>
				&lt;!ELEMENT person (age<b>+</b>)&gt;
				&lt;!ELEMENT age (&#35;PCDATA)&gt;
			</pre>			
		</article>
	</body>
</html>