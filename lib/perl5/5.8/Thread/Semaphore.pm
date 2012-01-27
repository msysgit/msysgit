package Thread::Semaphore;

use threads::shared;

our $VERSION = '2.01';

=head1 NAME

Thread::Semaphore - thread-safe semaphores

=head1 SYNOPSIS

    use Thread::Semaphore;
    my $s = new Thread::Semaphore;
    $s->down;	# Also known as the semaphore P operation.
    # The guarded section is here
    $s->up;	# Also known as the semaphore V operation.

    # The default semaphore value is 1.
    my $s = new Thread::Semaphore($initial_value);
    $s->down($down_value);
    $s->up($up_value);

=head1 DESCRIPTION

Semaphores provide a mechanism to regulate access to resources. Semaphores,
unlike locks, aren't tied to particular scalars, and so may be used to
control access to anything you care to use them for.

Semaphores don't limit their values to zero or one, so they can be used to
control access to some resource that there may be more than one of. (For
example, filehandles.) Increment and decrement amounts aren't fixed at one
either, so threads can reserve or return multiple resources at once.

=head1 FUNCTIONS AND METHODS

=over 8

=item new

=item new NUMBER

C<new> creates a new semaphore, and initializes its count to the passed
number. If no number is passed, the semaphore's count is set to one.

=item down

=item down NUMBER

The C<down> method decreases the semaphore's count by the specified number,
or by one if no number has been specified. If the semaphore's count would drop
below zero, this method will block until such time that the semaphore's
count is equal to or larger than the amount you're C<down>ing the
semaphore's count by.

This is the semaphore "P operation" (the name derives from the Dutch
word "pak", which means "capture" -- the semaphore operations were
named by the late Dijkstra, who was Dutch).

=item up

=item up NUMBER

The C<up> method increases the semaphore's count by the number specified,
or by one if no number has been specified. This will unblock any thread blocked
trying to C<down> the semaphore if the C<up> raises the semaphore count
above the amount that the C<down>s are trying to decrement it by.

This is the semaphore "V operation" (the name derives from the Dutch
word "vrij", which means "release").

=back

=cut

sub new {
    my $class = shift;
    my $val : shared = @_ ? shift : 1;
    bless \$val, $class;
}

sub down {
    my $s = shift;
    lock($$s);
    my $inc = @_ ? shift : 1;
    cond_wait $$s until $$s >= $inc;
    $$s -= $inc;
}

sub up {
    my $s = shift;
    lock($$s);
    my $inc = @_ ? shift : 1;
    ($$s += $inc) > 0 and cond_broadcast $$s;
}

1;
