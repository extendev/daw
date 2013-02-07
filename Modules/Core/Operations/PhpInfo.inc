<?php

namespace Daw\Modules\Core\Operations;

class PhpInfo extends \Daw\Core\Module\Operation {

    public function run($args = array()) {
        return phpinfo();
    }
}
