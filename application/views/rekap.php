<div class="row mt-3">
	<div class="col-lg-12">
		<div class="card">
			<div class="card-body">
				<div class="table-responsive">
					<table class="table table-bordered table-hover">
						<tr>
							<th>#</th>
							<th>Tinggi Air</th>
							<th>Tinggi Limpasan Air</th>
							<th>Tanggal</th>
							<th>Action</th>
						</tr>

						<?php foreach ($data as $i => $dt) : ?>
							<tr>
								<td><?= $i + 1; ?></td>
								<td><?= $dt->tinggiAir; ?></td>
								<td><?= $dt->tinggiLimpasan; ?></td>
								<td><?= date('d M Y - H:i:s', strtotime($dt->createdAt)); ?></td>
								<td>
									<a href="<?= base_url('rekap/delete/' . $dt->id); ?>" class="btn btn-danger">Delete</a>
								</td>
							</tr>
						<?php endforeach; ?>
					</table>
				</div>
			</div>
		</div>
	</div>
</div>