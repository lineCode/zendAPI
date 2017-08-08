--TEST--
Class register test
--FILE--
<?php
if (class_exists("Person")) {
   echo "class Person exist";
}
var_dump(new Person);
$person = new Person;
$person = new Person;
$person1 = new Person;
var_dump($person);
var_dump($person::$staticProp);
var_dump(defined("Person::MY_CONST"));
var_dump(Person::MY_CONST);
var_dump(defined("Person::PI"));
var_dump(Person::PI);
var_dump($person->name);
var_dump(interface_exists("InfoProvider"));
var_dump(method_exists("InfoProvider", "getName"));
var_dump($person instanceof InfoProvider);
var_dump(function_exists("zapi\\get_name"));
var_dump(function_exists("zapi\\io\\print_name"));
var_dump(function_exists("zapi\\io\\show_something"));
var_dump(defined("zapi\\SYS_VERSION"));
var_dump(class_exists("zapi\\Address"));
\zapi\io\print_name("wangyang");
?>
--EXPECT--
zapi v0.0.1 hello world, zapi


