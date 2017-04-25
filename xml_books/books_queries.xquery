xquery version "1.0";

(: Generated with EditiX at Sun Apr 23 20:31:07 IST 2017 :)

let $books:= (doc("/home/obed/editix2/books.xml")/books/book)
return<results>
{
for $x in $books
where $x/price>30
order by $x/price
return $x/title
}</results>
