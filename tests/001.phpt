--TEST--
Check if l5_model is loaded
--SKIPIF--
<?php
if (!extension_loaded('l5_model')) {
	echo 'skip';
}
?>
--FILE--
<?php 
echo 'The extension "l5_model" is available';
?>
--EXPECT--
The extension "l5_model" is available
