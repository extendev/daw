<?php

namespace Daw\Modules\Core\Operations;

class ModuleList extends \Daw\Core\Module\Operation {

    public function run($args = array()) {
        $moduleList = array();
        foreach ($this->core->getModules() as $module) {
            $moduleOperations = array();
            foreach ($module->operationList() as $operation) {
                $moduleOperations[] = array_merge(
                    array(
                        'label' => $operation->getName(),
                        'module' => $module->getName()
                    ),
                    $operation->info()
                );
            }
            $moduleInfo = array_merge($module->info(), array('operations' => $moduleOperations));
            $moduleList[$module->getName()] = new \Daw\Core\Object\Module($moduleInfo);
        }

        return $moduleList;
    }
}
