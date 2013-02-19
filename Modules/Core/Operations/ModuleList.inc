<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this module source code.
 */

namespace Daw\Modules\Core\Operations;

/**
 * Module List Operation
 * Return the list of modules enabled on the application
 *
 * @package Modules/Core
 * @subpackage Operations
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class ModuleList extends \Daw\Core\Module\Operation {

    /**
     * Run the operation
     *
     * @param $args arguments
     * @return string response validating deletion of the site
     * @see Daw\Core\Module.Operation::run()
     */
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
