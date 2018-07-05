--TEST--
l5_model_test2() Basic test
--SKIPIF--
<?php
if (!extension_loaded('l5_model')) {
	echo 'skip';
}
?>
--FILE--
<?php 
var_dump(l5_model_test2());
var_dump(l5_model_test2('PHP'));
?>
--EXPECT--
string(11) "Hello World"
string(9) "Hello PHP"
