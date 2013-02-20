<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Common;

/**
 * Application Common Utils - FileUtils
 *
 * Collection of utility functions for files
 *
 * @package Daw
 * @subpackage Common
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class FileUtil {

    /**
     * Concatenate path
     *
     * Concatenate as many fragments passed to the method
     * using DIRECTORY_SEPARATOR
     *
     * @return string concatenated path
     */
    public static function concat(/*$path, $path2, ...*/) {
        $args = func_get_args();
        $consolidatedString = rtrim(array_shift($args), DIRECTORY_SEPARATOR);
        foreach ($args as $arg) {
            $consolidatedString .= DIRECTORY_SEPARATOR . ltrim($arg, DIRECTORY_SEPARATOR);
        }

        return $consolidatedString;
    }
}
