<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Formatter;

use \Daw\Core\Common\Enum;

/**
 * Available formats Enumeration
 *
 * @package Daw
 * @subpackage Formatters
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class Format extends Enum {

    /**
     * @var string[] enumeration constants
     */
    protected final $constants = array(
        'JSON', 'Yaml'
    );
}
