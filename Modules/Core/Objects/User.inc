<?php

namespace Daw\Modules\Core\Objects;

class User extends \Daw\Core\Object\Object  {

    protected $name;
    protected $username;
    protected $password;
    protected $email;
    protected $active;

    public function primaryKey() {
        return 'username';
    }
}
