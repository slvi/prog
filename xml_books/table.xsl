<?xml version="1.0" encoding="UTF-8"?>

<!-- New document created with EditiX at Sun Apr 23 20:58:57 IST 2017 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output method="html"/>
	
	<xsl:template match="/">
	<html>
		<body>
		<h2>Books</h2>
		<table border="1" >
		<tr>
		<th>Title</th>
		<th>Price</th>
		</tr>
		<xsl:for-each select="books/book">
		<tr>
		<td><xsl:value-of select="title"/></td>
		<td><xsl:value-of select="price"/></td>
		</tr>
		
		
		</xsl:for-each>
		
		
		</table>
		</body>
	</html>
	</xsl:template>

</xsl:stylesheet>


