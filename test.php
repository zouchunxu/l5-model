<?php
$obj = new Model();
/*
        &host,&host_len,&user_name,&user_name_len,
        &password,&password_len,&database,&database_len,&port
*/
$host = "127.0.0.1";
$user = "root";
$password = "dev";
$database = "test";
$obj->connect($host,$user,$password,$database,3306);
//var_dump($obj->insert('select * from user'));
var_dump($obj->select('select * from user limit 1'));
//var_dump($obj->select('select * from user'));

//l5_model_test1($host,$user,$password,$database);