<?php

namespace Daw\Modules\Core\Operations;

class ObjectOptionList extends \Daw\Core\Module\Operation {

    public function run($args = array()) {

        $objectName = $this->getArg('object');
        $key = $this->getArg('key');
        $value = $this->getArg('value');

        $options = array();
        foreach ($this->core->getObjectStore($objectName)->search() as $object) {
            $options[$object->$key] = $object->$value;
        }

        return $options;
    }
}
