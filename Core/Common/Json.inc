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
 * Application Common Utils - JSON
 *
 * @package Daw
 * @subpackage Common
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class Json {


    /**
     * Encode object as a JSON string
     *
     * @param object $data object to encode
     * @return string JSON encoded data
     */
    public static function encode($data) {
        return json_encode($data);
    }

    /**
     * Encode array as a JSON string
     *
     * @param object $data object to encode
     * @return string JSON encoded data
     */
    public static function encodeArray($data) {
        $jsonData = '[]';
        if (is_array($data) && count($data)) {
            $array = array();
            foreach ($data as $record) {
                $array[] = $record;
            }

            $jsonData = json_encode($array);
        }

        return $jsonData;
    }

    /**
     * Encode hashtable as a JSON string
     *
     * @param object $data object to encode
     * @return string JSON encoded data
     */
    public static function encodeHashtable($data) {
        $jsonData = '{}';
        if (is_array($data) && count($data)) {
            $jsonData = json_encode($data);
        }

        return $jsonData;
    }

    /**
     * Decode JSON data
     *
     * @param string $jsonData JSON data to decode
     * @param boolean $asArray shall the resulting object be an array or object
     */
    public static function decode($jsonData, $asArray = false) {
        return json_decode($jsonData, $asArray);
    }
}
