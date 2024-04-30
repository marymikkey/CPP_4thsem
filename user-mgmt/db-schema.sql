create table user(
    id text primary key,
    name text
);
create table "group"(
    id text primary key
);
create table user_group (
    user text,
    "group" text,
    foreign key (user) references user(id),
    foreign key ("group") references "group"(id),
    primary key ("group", user)
);
