.. currentmodule:: ACEtk.multigroup

P0LocatorBlock
==============

The `P0L` block holds the locators for the `P0` blocks within the XSS array.
These locators are absolute within the full XSS array. 
There are `NSEC` secondary particles and `NSEC` +1 `P0` blocks, which do not need to be contiguous.
The first locator is the `P0` block for the incident particle, and the rest are the for the secondary particles in the same order as in the :class:`SecondaryParticleTypeBlock`.

There are separate functions on the :class:`P0LocatorBlock` object to return the locator for the incident particle and for the secondary particles.
This is to allow consistency with the indices of the secondary particles in the :class:`SecondaryParticleTypeBlock` block.

Constructors
~~~~~~~~~~~~
.. autosummary::
    :toctree:  generated/

    ~P0LocatorBlock


ACE Variables
~~~~~~~~~~~~~
.. autosummary::
    :toctree: generated/

    ~P0LocatorBlock.NSEC
    ~P0LocatorBlock.P01
    ~P0LocatorBlock.P02
    ~P0LocatorBlock.xss

Human-Readable Variables
~~~~~~~~~~~~~~~~~~~~~~~~
.. autosummary::
    :toctree: generated/
    
    ~P0LocatorBlock.number_secondary_particle_types
    ~P0LocatorBlock.incident_locator
    ~P0LocatorBlock.secondary_locator
    ~P0LocatorBlock.empty
    ~P0LocatorBlock.length
    ~P0LocatorBlock.name
    ~P0LocatorBlock.xss_array



