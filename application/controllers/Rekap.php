<?php

defined('BASEPATH') or exit('No direct script access allowed');

class Rekap extends CI_Controller
{
	public function index()
	{
		$this->db->order_by('id', 'desc');
		$rekap = $this->db->get('data')->result();

		$data = [
			'title' => 'Rekap Data',
			'page' => 'rekap',
			'data' => $rekap
		];

		$this->load->view('index', $data);
	}

	public function delete($id)
	{
		$this->db->where('id', $id);
		$this->db->delete('data');

		redirect('rekap', 'refresh');
	}
}

/* End of file Rekap.php */
