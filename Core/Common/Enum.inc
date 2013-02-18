<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Common;

/**
 * Application Common Utils - Enumeration base class
 *
 * @package Daw
 * @subpackage Common
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
abstract class Enum {

    /**
     * @var string[] $constants list of enumeration constants
     */
    protected $constants = array();

    /**
     * Return the enumeration value for the specifid string
     * Throws EnumInvalidValueException if could not be found
     *
     * @param string $value value to find in enumeration
     * @return string
     * @throws EnumInvalidValueException if value is not included in the enumeration
     */
    public static function parseValue($value) {
        foreach (static::constants as $constant) {
            if ($value === $constant) {
                return $value;
            }
        }

        throw new EnumInvalidValueException();
    }

    /**
     * Return list of enum values
     *
     * @return string[] list of enumeration values
     */
    public static function values() {
        return static::constants;
    }
}
