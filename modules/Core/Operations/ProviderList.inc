<?php

namespace Daw\Modules\Core\Operations;

class ProviderList extends \Daw\Core\Module\Operation {

	public function run($args = array()) {
		$list = array();

		foreach ($this->core->getProviders() as $feature => $providers) {
			$list[$feature] = array(
				'default' => null,
				'available' => array(),
				'config' => $this->core->config($feature)
			);

			foreach ($providers as $provider) {
				$list[$feature]['available'][] = get_class($provider);
			}

			$list[$feature]['default'] = get_class($this->core->$feature);
		}

		return $list;
	}
}
