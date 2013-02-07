<?php

namespace Daw\Modules\Core\Operations;

class Info extends \Daw\Core\Module\Operation {

    public function run($args = array()) {
        return $this->core->config();
    }
}
