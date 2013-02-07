<?php

namespace Daw\Modules\Core\Operations;

class ObjectList extends \Daw\Core\Module\Operation {

    public function run($args = array()) {
        $objectList = array();
        foreach ($this->core->getObjects() as $objectName => $object) {
            $objectList[$objectName] = array(
                'operations' => $this->core->getOperations($objectName)
            );
        }

        return $objectList;
    }
}
