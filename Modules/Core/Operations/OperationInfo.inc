<?php

namespace Daw\Modules\Core\Operations;

use \Daw\Core\Exception\OperationException;
use \Daw\Core\Exception\OperationArgumentException;

class OperationInfo extends \Daw\Core\Module\Operation {

    /**
     * Operation execution
     *
     * @see Daw\Core\Module.Operation::run()
     */
    public function run($args = array()) {
        $this->validate($args);

        $operation = $this->core->getOperation($args['object'], $args['operation']);
        if ($operation === false) {
            throw new OperationException($this, 'No operation found for given arguments', 405);
        }

        return $operation->info();
    }
}
