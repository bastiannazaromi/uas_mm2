<?php

defined('BASEPATH') or exit('No direct script access allowed');

class Dashboard extends CI_Controller
{
	public function index()
	{
		$this->db->order_by('id', 'desc');
		$rekap = $this->db->get('data', 1)->row();

		$data = [
			'title' => 'Dashboard',
			'page' => 'dashboard',
			'data' => $rekap
		];

		$this->load->view('index', $data);
	}
}

/* End of file Dashboard.php */
