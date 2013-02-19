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
 * Site Delete Operation
 * Delete a site from existing list of CerberHost sites
 *
 * @package Modules/Core
 * @subpackage Operations
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class Info extends \Daw\Core\Module\Operation {

    /**
     * Run the operation
     *
     * @param $args arguments
     * @return string response validating deletion of the site
     * @see Daw\Core\Module.Operation::run()
     */
    public function run($args = array()) {
        return $this->core->config();
    }
}
