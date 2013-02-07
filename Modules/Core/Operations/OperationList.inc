<?php

namespace Daw\Modules\Core\Operations;

class OperationList extends \Daw\Core\Module\Operation {

    public function run($args = array()) {
        $list = array();
        foreach ($this->core->getOperations() as $operation) {
            $index = '(' . $operation['module'] . ') ' . $operation['label'];
            $list[$index] = $operation;
        }

        return $list;
    }
}
