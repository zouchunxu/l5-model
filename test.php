<?php
$obj = new Model();
/*
        &host,&host_len,&user_name,&user_name_len,
        &password,&password_len,&database,&database_len,&port
*/
$obj->connect("127.0.0.1","root","dev","test",3306);

