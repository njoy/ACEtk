.. currentmodule:: ACEtk.multigroup

PNLocatorBlock
==============

The `PNL` block holds the locators for the `PN` blocks within the XSS array.
These locators are absolute within the full XSS array. 
There are `NSEC` secondary particles and `NSEC` +1 `PN` blocks, which do not need to be contiguous.
The first locator is the `PN` block for the incident particle, and the rest are the for the secondary particles in the same order as in the :class:`SecondaryParticleTypeBlock`.

There are separate functions on the :class:`PNLocatorBlock` object to return the locator for the incident particle and for the secondary particles.
This is to allow consistency with the indices of the secondary particles in the :class:`SecondaryParticleTypeBlock` block.

Constructors
~~~~~~~~~~~~
.. autosummary::
    :toctree:  generated/

    ~PNLocatorBlock


ACE Variables
~~~~~~~~~~~~~
.. autosummary::
    :toctree: generated/

    ~PNLocatorBlock.NSEC
    ~PNLocatorBlock.LPN
    ~PNLocatorBlock.LPN1
    ~PNLocatorBlock.xss

Human-Readable Variables
~~~~~~~~~~~~~~~~~~~~~~~~
.. autosummary::
    :toctree: generated/
    
    ~PNLocatorBlock.number_secondary_particle_types
    ~PNLocatorBlock.secondary_locator
    ~PNLocatorBlock.incident_locator
    ~PNLocatorBlock.is_isotropic
    ~PNLocatorBlock.incident_isotropic
    ~PNLocatorBlock.empty
    ~PNLocatorBlock.length
    ~PNLocatorBlock.name
    ~PNLocatorBlock.xss_array



