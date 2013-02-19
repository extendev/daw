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
 * Object OptionList Operation
 *
 * Return the key/value pair list extracted from all objects currently stored
 * in the application, where key and value are set with properties of the object
 * that you will define
 *
 * @package Modules/Core
 * @subpackage Operations
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class ObjectOptionList extends \Daw\Core\Module\Operation {

    /**
     * Run the operation
     *
     * @param $args arguments
     * @return string response validating deletion of the site
     * @see Daw\Core\Module.Operation::run()
     */
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
