create table if not exists employees (
	employee_id SERIAL primary key,
	employee_name VARCHAR(60) not null,
	department VARCHAR(60) unique not null,
	supervisor_id INTEGER references employees(employee_id)
); 