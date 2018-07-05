--TEST--
l5_model_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('l5_model')) {
	echo 'skip';
}
?>
--FILE--
<?php 
$ret = l5_model_test1();

var_dump($ret);
?>
--EXPECT--
The extension l5_model is loaded and working!
NULL
