<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Module\Operation\Argument;

/**
 * Application Module - Argument Update List
 *
 * This object is used to define how a list shall be updated
 * by either replacing all data, adding or removing data
 *
 * It contains 3 properties: set (for replacing), added (for adding)
 * and removed (for removing).
 *
 * You can then apply all the changes to a given list by calling update
 * method on it
 *
 * @package Daw
 * @subpackage Module
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class UpdateList {

    /**
     * @var array data to be added
     */
    public $added = array();

    /**
     * @var array data to be removed
     */
    public $removed = array();

    /**
     * @var array data to be set
     */
    public $set = array();


    /**
     * Constructor
     *
     * @param
     */
    public function __construct($list = array()) {
        foreach ($list as $idx => $value) {
            if ($value[0] === '-') {
                $this->removed[] = substr($value, 1);
            } elseif ($value[0] === '+') {
                $this->added[] = substr($value, 1);
            } else {
                $this->set[] = $value;
            }
        }
    }

    /**
     * Update specified with data set in this object
     *
     * @param mixed[] $list list to be updated
     * @return mixed[] the resulting list
     */
    public function update($list) {
        if ($this->set) {
            $list = $this->set;
        }
        if (isset($this->added)) {
            $list = array_merge($list, $this->added);
        }
        if (isset($this->removed)) {
            $list = array_diff($list, $this->removed);
        }

        return $list;
    }
}


