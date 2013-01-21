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

/**
 * Application Formatter abstract base class
 *
 * To create your own formatter, extend this class and define
 * which objects this formatter shall render by setting the
 * isFormatterFor method.
 *
 * @package Daw
 * @subpackage Formatters
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
abstract class Formatter {

	/**
	 * @var Daw\Core\Core Core instance
	 */
	protected $core = null;

	/**
	 * @var FormatterContext Formatter context
	 */
	protected $context = null;


	/**
	 * Constructor
	 *
	 * @param Daw\Core\Core $core
	 */
	public function __construct($core) {
		$this->core = $core;
	}

	/**
	 * Set current formatting context
	 *
	 * @param FormatterContext $context
	 */
	public function setContext($context) {
		$this->context = $context;
	}

	/**
	 * Return true if formatter supports given object and possibly given format
	 *
	 * @param object $object object to render
	 * @param Daw\Core\Formatter\Format $format format to be used for rendering
	 * @return boolean
	 */
	public abstract function isFormatterFor($object, $format = null);

	/**
	 * Render object passed as first argument.
	 *
	 * Format to be used for renderring the object is passed as second argument
	 * in case the formatter supports multiple formats
	 *
	 * @param object $object object to render
	 * @param Daw\Core\Formatter\Format $format format to be used for rendering
	 * @return
	 */
	public abstract function render($object, $format);
}