from __future__ import annotations
import pybind11_stubgen.typing_ext
import typing
import typing_extensions
from . import continuous
from . import dosimetry
from . import electron
from . import photoatomic
from . import photonuclear
from . import sequence
from . import thermal
__all__ = ['AngularDistributionType', 'ContinuousEnergyTable', 'Data', 'DosimetryTable', 'EnergyDistributionType', 'Header', 'Header201', 'PhotoatomicTable', 'PhotonuclearTable', 'ReferenceFrame', 'Table', 'ThermalScatteringTable', 'Xsdir', 'XsdirEntry', 'continuous', 'dosimetry', 'electron', 'photoatomic', 'photonuclear', 'sequence', 'thermal']
class AngularDistributionType:
    """
    The angular distribution types
    
    Members:
    
      Isotropic
    
      Equiprobable
    
      Tabulated
    """
    Equiprobable: typing.ClassVar[AngularDistributionType]  # value = <AngularDistributionType.Equiprobable: 1>
    Isotropic: typing.ClassVar[AngularDistributionType]  # value = <AngularDistributionType.Isotropic: 0>
    Tabulated: typing.ClassVar[AngularDistributionType]  # value = <AngularDistributionType.Tabulated: 2>
    __members__: typing.ClassVar[dict[str, AngularDistributionType]]  # value = {'Isotropic': <AngularDistributionType.Isotropic: 0>, 'Equiprobable': <AngularDistributionType.Equiprobable: 1>, 'Tabulated': <AngularDistributionType.Tabulated: 2>}
    def __eq__(self, other: typing.Any) -> bool:
        ...
    def __ge__(self, other: typing.Any) -> bool:
        ...
    def __getstate__(self) -> int:
        ...
    def __gt__(self, other: typing.Any) -> bool:
        ...
    def __hash__(self) -> int:
        ...
    def __index__(self) -> int:
        ...
    def __init__(self, value: int) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __le__(self, other: typing.Any) -> bool:
        ...
    def __lt__(self, other: typing.Any) -> bool:
        ...
    def __ne__(self, other: typing.Any) -> bool:
        ...
    def __repr__(self) -> str:
        ...
    def __setstate__(self, state: int) -> None:
        ...
    def __str__(self) -> str:
        ...
    @property
    def name(self) -> str:
        ...
    @property
    def value(self) -> int:
        ...
class ContinuousEnergyTable:
    """
    A continuous energy ACE table
    
    The ContinuousEnergyTable class represents the ACE table for continuous
    energy data for incident neutrons and charged particles.
    """
    @staticmethod
    def from_concatenated_file(arg0: str) -> list[ContinuousEnergyTable]:
        """
        Read ACE tables from a concatenated file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    @staticmethod
    def from_file(arg0: str) -> ContinuousEnergyTable:
        """
        Read an ACE table from a file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    def ANDH(self, index: int) -> continuous.SecondaryParticleAngularDistributionBlock:
        """
        Return the angular distribution block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def DLWH(self, index: int) -> continuous.SecondaryParticleEnergyDistributionBlock:
        """
        Return the energy distribution block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def HPD(self, index: int) -> continuous.SecondaryParticleProductionBlock:
        """
        Return the secondary particle production block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def MTRH(self, index: int) -> continuous.ReactionNumberBlock:
        """
        Return the reaction number block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def SIGH(self, index: int) -> continuous.SecondaryParticleProductionCrossSectionBlock:
        """
        Return the production cross section block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def TYRH(self, index: int) -> continuous.FrameAndMultiplicityBlock:
        """
        Return the reference frame and multiplicity block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def YH(self, index: int) -> continuous.MultiplicityReactionNumberBlock:
        """
        Return the multiplicity reaction number block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, z: int, a: int, s: int, header: Header | Header201, esz: continuous.PrincipalCrossSectionBlock, nu: continuous.FissionMultiplicityBlock | None = None, dnu: continuous.FissionMultiplicityBlock | None = None, mtr: continuous.ReactionNumberBlock, lqr: continuous.ReactionQValueBlock, sig: continuous.CrossSectionBlock, ang: continuous.AngularDistributionBlock, dlw: continuous.EnergyDistributionBlock, bdd: continuous.DelayedNeutronPrecursorBlock | None = None, dned: continuous.SecondaryParticleEnergyDistributionBlock | None = None, gpd: continuous.PhotonProductionBlock | None = None, mtrp: continuous.ReactionNumberBlock | None = None, sigp: continuous.PhotonProductionCrossSectionBlock | None = None, andp: continuous.SecondaryParticleAngularDistributionBlock | None = None, dlwp: continuous.SecondaryParticleEnergyDistributionBlock | None = None, yp: continuous.MultiplicityReactionNumberBlock | None = None, unr: continuous.ProbabilityTableBlock | None = None, ptype: continuous.SecondaryParticleTypeBlock | None = None, hpd: list[continuous.SecondaryParticleProductionBlock] | None = None, mtrh: list[continuous.ReactionNumberBlock] | None = None, sigh: list[continuous.SecondaryParticleProductionCrossSectionBlock] | None = None, andh: list[continuous.SecondaryParticleAngularDistributionBlock] | None = None, dlwh: list[continuous.SecondaryParticleEnergyDistributionBlock] | None = None, yh: list[continuous.MultiplicityReactionNumberBlock] | None = None) -> None:
        """
        Initialise the table
        
        Arguments:
            self      the table
            z         the Z number of the target
            a         the A number of the target
            s         the S number of the target
            header    the header for the table
            esz       the principal cross section block
            nu        the optional fission neutron multiplicity block
            dnu       the optional delayed fission neutron multiplicity block
            mtr       the reaction number block
            lqr       the reaction Q value block
            sig       the cross section data block
            ang       the angular distribution data block
            dlw       the energy distribution data block
            bdd       the delayed fission neutron precursor data block
            dned      the delayed fission neutron energy distribution data block
            gpd       the photon production block
            mtrp      the photon production reaction number block
            sigp      the photon production cross section data block
            angp      the photon production angular distribution data block
            dlwp      the photon production energy distribution data block
            yp        the photon multiplicity reaction number block
            unr       the unresolved resonance probability table block
            ptype     the secondary particle type block
            hpd       the secondary particle production blocks
            mtrh      the secondary particle production reaction number blocks
            sigh      the secondary particle production cross section data blocks
            andh      the secondary particle angular distribution data blocks
            dlwh      the secondary particle energy distribution data blocks
            yh        the secondary particle multiplicity reaction number blocks
        """
    def secondary_particle_angular_distribution_block(self, index: int) -> continuous.SecondaryParticleAngularDistributionBlock:
        """
        Return the angular distribution block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_energy_distribution_block(self, index: int) -> continuous.SecondaryParticleEnergyDistributionBlock:
        """
        Return the energy distribution block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_frame_and_multiplicity_block(self, index: int) -> continuous.FrameAndMultiplicityBlock:
        """
        Return the reference frame and multiplicity block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_multiplicity_reaction_number_block(self, index: int) -> continuous.MultiplicityReactionNumberBlock:
        """
        Return the multiplicity reaction number block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_production_block(self, index: int) -> continuous.SecondaryParticleProductionBlock:
        """
        Return the secondary particle production block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_production_cross_section_block(self, index: int) -> continuous.FrameAndMultiplicityBlock:
        """
        Return the production cross section block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_reaction_number_block(self, index: int) -> continuous.ReactionNumberBlock:
        """
        Return the reaction number block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def to_file(self, arg0: str) -> None:
        """
        Write the ACE table to a file
        
        Arguments:
            self        the table
            filename    the file name and path
        """
    @property
    def A(self) -> int:
        """
        The mass number of the target
        """
    @property
    def AND(self) -> continuous.AngularDistributionBlock:
        """
        The angular distribution block
        """
    @property
    def ANDP(self) -> continuous.SecondaryParticleAngularDistributionBlock | None:
        """
        The photon production angular distribution block
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def BDD(self) -> continuous.DelayedNeutronPrecursorBlock | None:
        """
        The delayed neutron precursor block
        """
    @property
    def DLW(self) -> continuous.EnergyDistributionBlock:
        """
        The energy distribution block
        """
    @property
    def DLWP(self) -> continuous.SecondaryParticleEnergyDistributionBlock | None:
        """
        The photon production energy distribution block
        """
    @property
    def DNED(self) -> continuous.SecondaryParticleEnergyDistributionBlock | None:
        """
        The delayed neutron energy distribution block
        """
    @property
    def DNU(self) -> continuous.FissionMultiplicityBlock | None:
        """
        The delayed fission multiplicity block
        """
    @property
    def ESZ(self) -> continuous.PrincipalCrossSectionBlock:
        """
        The principal cross section block
        """
    @property
    def GPD(self) -> continuous.PhotonProductionBlock | None:
        """
        The photon production block
        """
    @property
    def IXS(self) -> continuous.SecondaryParticleLocatorBlock | None:
        """
        The secondary particle locator block
        """
    @property
    def LQR(self) -> continuous.ReactionQValueBlock:
        """
        The reaction Q value block
        """
    @property
    def MTR(self) -> continuous.ReactionNumberBlock:
        """
        The reaction number block
        """
    @property
    def MTRP(self) -> continuous.ReactionNumberBlock | None:
        """
        The photon production reaction number block
        """
    @property
    def NES(self) -> int:
        """
        The number of energy points
        """
    @property
    def NPCR(self) -> int:
        """
        The number of delayed percursor families
        """
    @property
    def NR(self) -> int:
        """
        The number of reactions excluding elastic that produce the projectile
        """
    @property
    def NTR(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def NTRO(self) -> continuous.SecondaryParticleInformationBlock | None:
        """
        The secondary particle information block
        """
    @property
    def NTRP(self) -> int:
        """
        The number of reactions that produce photons
        """
    @property
    def NTYPE(self) -> int:
        """
        The number of secondary particle types (excluding the projectile and photons)
        """
    @property
    def NU(self) -> continuous.FissionMultiplicityBlock | None:
        """
        The fission multiplicity block
        """
    @property
    def PTYPE(self) -> continuous.SecondaryParticleTypeBlock | None:
        """
        The secondary particle type block
        """
    @property
    def S(self) -> int:
        """
        The isomeric state of the target
        """
    @property
    def SIG(self) -> continuous.CrossSectionBlock:
        """
        The cross section block
        """
    @property
    def SIGP(self) -> continuous.PhotonProductionCrossSectionBlock | None:
        """
        The photon production cross section block
        """
    @property
    def TEMP(self) -> float:
        """
        The temperature of the table
        """
    @property
    def TYR(self) -> continuous.FrameAndMultiplicityBlock:
        """
        The reference frame and multiplicity block
        """
    @property
    def UNR(self) -> continuous.ProbabilityTableBlock | None:
        """
        The unresolved probability table block
        """
    @property
    def YP(self) -> continuous.MultiplicityReactionNumberBlock | None:
        """
        The photon multiplicity reaction number block
        """
    @property
    def Z(self) -> int:
        """
        The atom number of the target
        """
    @property
    def angular_distribution_block(self) -> continuous.AngularDistributionBlock:
        """
        The angular distribution block
        """
    @property
    def atom_number(self) -> int:
        """
        The atom number of the target
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def cross_section_block(self) -> continuous.CrossSectionBlock:
        """
        The cross section block
        """
    @property
    def data(self) -> Data:
        """
        The data arrays
        """
    @property
    def date(self) -> str:
        """
        The date
        """
    @property
    def delayed_fission_multiplicity_block(self) -> continuous.FissionMultiplicityBlock | None:
        """
        The delayed fission multiplicity block
        """
    @property
    def delayed_neutron_energy_distribution_block(self) -> continuous.SecondaryParticleEnergyDistributionBlock | None:
        """
        The delayed neutron energy distribution block
        """
    @property
    def delayed_neutron_precursor_block(self) -> continuous.DelayedNeutronPrecursorBlock | None:
        """
        The delayed neutron precursor block
        """
    @property
    def energy_distribution_block(self) -> continuous.EnergyDistributionBlock:
        """
        The energy distribution block
        """
    @property
    def fission_multiplicity_block(self) -> continuous.FissionMultiplicityBlock | None:
        """
        The fission multiplicity block
        """
    @property
    def frame_and_multiplicity_block(self) -> continuous.FrameAndMultiplicityBlock:
        """
        The reference frame and multiplicity block
        """
    @property
    def header(self) -> Header | Header201:
        """
        The header information
        """
    @property
    def isomeric_state(self) -> int:
        """
        The isomeric state of the target
        """
    @property
    def length(self) -> int:
        """
        The total length of the XSS array
        """
    @property
    def mass_number(self) -> int:
        """
        The mass number of the target
        """
    @property
    def number_delayed_precursors(self) -> int:
        """
        The number of delayed percursor families
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of energy points
        """
    @property
    def number_photon_production_reactions(self) -> int:
        """
        The number of reactions that produce photons
        """
    @property
    def number_projectile_production_reactions(self) -> int:
        """
        The number of reactions excluding elastic that produce the projectile
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def number_secondary_particle_types(self) -> int:
        """
        The number of secondary particle types (excluding the projectile and photons)
        """
    @property
    def photon_multiplicity_reaction_number_block(self) -> continuous.MultiplicityReactionNumberBlock | None:
        """
        The photon multiplicity reaction number block
        """
    @property
    def photon_production_angular_distribution_block(self) -> continuous.SecondaryParticleAngularDistributionBlock | None:
        """
        The photon production angular distribution block
        """
    @property
    def photon_production_block(self) -> continuous.PhotonProductionBlock | None:
        """
        The photon production block
        """
    @property
    def photon_production_cross_section_block(self) -> continuous.CrossSectionBlock:
        """
        The photon production cross section block
        """
    @property
    def photon_production_energy_distribution_block(self) -> continuous.SecondaryParticleEnergyDistributionBlock | None:
        """
        The photon production energy distribution block
        """
    @property
    def photon_production_reaction_number_block(self) -> continuous.ReactionNumberBlock | None:
        """
        The photon production reaction number block
        """
    @property
    def principal_cross_section_block(self) -> continuous.PrincipalCrossSectionBlock:
        """
        The principal cross section block
        """
    @property
    def probability_table_block(self) -> continuous.ProbabilityTableBlock | None:
        """
        The unresolved probability table block
        """
    @property
    def reaction_number_block(self) -> continuous.ReactionNumberBlock:
        """
        The reaction number block
        """
    @property
    def reaction_qvalue_block(self) -> continuous.ReactionQValueBlock:
        """
        The reaction Q value block
        """
    @property
    def secondary_particle_information_block(self) -> continuous.SecondaryParticleInformationBlock | None:
        """
        The secondary particle information block
        """
    @property
    def secondary_particle_locator_block(self) -> continuous.SecondaryParticleLocatorBlock | None:
        """
        The secondary particle locator block
        """
    @property
    def secondary_particle_type_block(self) -> continuous.SecondaryParticleTypeBlock | None:
        """
        The secondary particle type block
        """
    @property
    def temperature(self) -> float:
        """
        The temperature of the table
        """
    @property
    def total_number_reactions(self) -> int:
        """
        The total number of available reactions (including elastic)
        """
    @property
    def za(self) -> int:
        """
        The ZA of the target
        """
    @property
    def zaid(self) -> str:
        """
        The full ZAID or SZAID of the table
        """
class Data:
    """
    The data in an ACE table
    
    The data in an ACE table consists of the following arrays:
      - the IZAW array which contains 16 integer, double pairs
      - the NXS array which contains information needed to properly interpret
        the XSS array
      - the JXS array which contains 32 locators to specific blocks in the
        XSS array (the meaning of the JXS locators depend on the type of the
        ACE table)
      - the XSS array which contains the actual data
    """
    @staticmethod
    def from_string(string: str) -> Data:
        """
        Read the ACE data arrays from a string
        
        An exception is raised if something goes wrong while reading the
        data arrays
        
        Arguments:
            string    the string representing the ACE data arrays
        """
    def __init__(self, iz: typing_extensions.Annotated[list[int], pybind11_stubgen.typing_ext.FixedSize(16)], aw: typing_extensions.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(16)], nxs: typing_extensions.Annotated[list[int], pybind11_stubgen.typing_ext.FixedSize(16)], jxs: typing_extensions.Annotated[list[int], pybind11_stubgen.typing_ext.FixedSize(32)], xss: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the data arrays
            iz      the IZ array
            aw      the AW array
            nxs     the NXS array
            jxs     the JXS array
            xss     the XSS array
        """
    def aw(self, index: int) -> float:
        """
        Return a value from the AW array
        
        Arguments:
            self     the data arrays
            index    the index (one-based)
        """
    def iz(self, index: int) -> int:
        """
        Return a value from the IZ array
        
        Arguments:
            self     the data arrays
            index    the index (one-based)
        """
    def jxs(self, index: int) -> int:
        """
        Return a value from the JXS array
        
        Arguments:
            self     the data arrays
            index    the index (one-based)
        """
    def nxs(self, index: int) -> int:
        """
        Return a value from the NXS array
        
        Arguments:
            self     the data arrays
            index    the index (one-based)
        """
    def to_string(self) -> str:
        """
        Return the string representation of the ACE data arrays
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the XSS array
        
        Arguments:
            self     the data arrays
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the XSS array
        
        Arguments:
            self      the data arrays
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def aw_array(self) -> typing_extensions.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(16)]:
        """
        The aw array
        """
    @property
    def iz_array(self) -> typing_extensions.Annotated[list[int], pybind11_stubgen.typing_ext.FixedSize(16)]:
        """
        The iz array
        """
    @property
    def jxs_array(self) -> typing_extensions.Annotated[list[int], pybind11_stubgen.typing_ext.FixedSize(32)]:
        """
        The jxs array
        """
    @property
    def nxs_array(self) -> typing_extensions.Annotated[list[int], pybind11_stubgen.typing_ext.FixedSize(16)]:
        """
        The nxs array
        """
    @property
    def xss_array(self) -> list[float]:
        """
        The xss array
        """
class DosimetryTable:
    """
    A dosimetry ACE table
    
    The DosimetryTable class represents the ACE table for dosimetry data.
    """
    @staticmethod
    def from_concatenated_file(arg0: str) -> list[DosimetryTable]:
        """
        Read ACE tables from a concatenated file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    @staticmethod
    def from_file(arg0: str) -> DosimetryTable:
        """
        Read an ACE table from a file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    def __init__(self, z: int, a: int, header: Header | Header201, mtr: continuous.ReactionNumberBlock, sigd: dosimetry.CrossSectionBlock) -> None:
        """
        Initialise the table
        
        Arguments:
            self      the table
            z         the Z number of the target
            a         the A number of the target
            header    the header for the table
            mtr       the reaction number block
            sigd      the cross section data block
        """
    def to_file(self, arg0: str) -> None:
        """
        Write the ACE table to a file
        
        Arguments:
            self        the table
            filename    the file name and path
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def MTR(self) -> continuous.ReactionNumberBlock:
        """
        The reaction number block
        """
    @property
    def NTR(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def SIGD(self) -> dosimetry.CrossSectionBlock:
        """
        The cross section block
        """
    @property
    def TEMP(self) -> float:
        """
        The temperature of the table
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def cross_section_block(self) -> dosimetry.CrossSectionBlock:
        """
        The cross section block
        """
    @property
    def data(self) -> Data:
        """
        The data arrays
        """
    @property
    def date(self) -> str:
        """
        The date
        """
    @property
    def header(self) -> Header | Header201:
        """
        The header information
        """
    @property
    def length(self) -> int:
        """
        The total length of the XSS array
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def reaction_number_block(self) -> continuous.ReactionNumberBlock:
        """
        The reaction number block
        """
    @property
    def temperature(self) -> float:
        """
        The temperature of the table
        """
    @property
    def za(self) -> int:
        """
        The ZA of the target
        """
    @property
    def zaid(self) -> str:
        """
        The full ZAID or SZAID of the table
        """
class EnergyDistributionType:
    """
    The energy distribution types
    
    Members:
    
      Equiprobable
    
      DiscretePhoton
    
      LevelScattering
    
      TabulatedEnergy
    
      GeneralEvaporation
    
      SimpleMaxwellianFission
    
      Evaporation
    
      Watt
    
      TwoBodyTransfer
    
      KalbachMann
    
      TabulatedEnergyAngle
    
      NBodyPhaseSpace
    
      TabulatedAngleEnergy
    
      MultiDistribution
    """
    DiscretePhoton: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.DiscretePhoton: 2>
    Equiprobable: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.Equiprobable: 1>
    Evaporation: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.Evaporation: 9>
    GeneralEvaporation: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.GeneralEvaporation: 5>
    KalbachMann: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.KalbachMann: 44>
    LevelScattering: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.LevelScattering: 3>
    MultiDistribution: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.MultiDistribution: 666>
    NBodyPhaseSpace: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.NBodyPhaseSpace: 66>
    SimpleMaxwellianFission: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.SimpleMaxwellianFission: 7>
    TabulatedAngleEnergy: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.TabulatedAngleEnergy: 67>
    TabulatedEnergy: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.TabulatedEnergy: 4>
    TabulatedEnergyAngle: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.TabulatedEnergyAngle: 61>
    TwoBodyTransfer: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.TwoBodyTransfer: 33>
    Watt: typing.ClassVar[EnergyDistributionType]  # value = <EnergyDistributionType.Watt: 11>
    __members__: typing.ClassVar[dict[str, EnergyDistributionType]]  # value = {'Equiprobable': <EnergyDistributionType.Equiprobable: 1>, 'DiscretePhoton': <EnergyDistributionType.DiscretePhoton: 2>, 'LevelScattering': <EnergyDistributionType.LevelScattering: 3>, 'TabulatedEnergy': <EnergyDistributionType.TabulatedEnergy: 4>, 'GeneralEvaporation': <EnergyDistributionType.GeneralEvaporation: 5>, 'SimpleMaxwellianFission': <EnergyDistributionType.SimpleMaxwellianFission: 7>, 'Evaporation': <EnergyDistributionType.Evaporation: 9>, 'Watt': <EnergyDistributionType.Watt: 11>, 'TwoBodyTransfer': <EnergyDistributionType.TwoBodyTransfer: 33>, 'KalbachMann': <EnergyDistributionType.KalbachMann: 44>, 'TabulatedEnergyAngle': <EnergyDistributionType.TabulatedEnergyAngle: 61>, 'NBodyPhaseSpace': <EnergyDistributionType.NBodyPhaseSpace: 66>, 'TabulatedAngleEnergy': <EnergyDistributionType.TabulatedAngleEnergy: 67>, 'MultiDistribution': <EnergyDistributionType.MultiDistribution: 666>}
    def __eq__(self, other: typing.Any) -> bool:
        ...
    def __ge__(self, other: typing.Any) -> bool:
        ...
    def __getstate__(self) -> int:
        ...
    def __gt__(self, other: typing.Any) -> bool:
        ...
    def __hash__(self) -> int:
        ...
    def __index__(self) -> int:
        ...
    def __init__(self, value: int) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __le__(self, other: typing.Any) -> bool:
        ...
    def __lt__(self, other: typing.Any) -> bool:
        ...
    def __ne__(self, other: typing.Any) -> bool:
        ...
    def __repr__(self) -> str:
        ...
    def __setstate__(self, state: int) -> None:
        ...
    def __str__(self) -> str:
        ...
    @property
    def name(self) -> str:
        ...
    @property
    def value(self) -> int:
        ...
class Header:
    """
    The header in an ACE table
    """
    @staticmethod
    def from_string(string: str) -> Header:
        """
        Read the ACE header from a string
        
        An exception is raised if something goes wrong while reading the
        header
        
        Arguments:
            string    the string representing the ACE header
        """
    def __init__(self, zaid: str, awr: float, temperature: float, date: str, title: str, material: str) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the header
            zaid           the zaid (max 10 characters)
            awr            the atomic weight ratio (to the neutron mass)
            temperature    the temperature in MeV
            date           the date (max 10 characters)
            title          the title (max 70 characters)
            material       the material (max 10 characters)
        """
    def to_string(self) -> str:
        """
        Return the string representation of the ACE table
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def TEMP(self) -> float:
        """
        The temperature of the table
        """
    @property
    def VERS(self) -> str:
        """
        The header version
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def date(self) -> str:
        """
        The date
        """
    @property
    def material(self) -> str:
        """
        The material
        """
    @property
    def temperature(self) -> float:
        """
        The temperature of the table
        """
    @property
    def title(self) -> str:
        """
        The title
        """
    @property
    def version(self) -> str:
        """
        The header version
        """
    @property
    def zaid(self) -> str:
        """
        The full ZAID or SZAID of the table
        """
class Header201:
    """
    The header in an ACE table
    """
    @staticmethod
    def from_string(string: str) -> Header201:
        """
        Read the ACE header from a string
        
        An exception is raised if something goes wrong while reading the
        header
        
        Arguments:
            string    the string representing the ACE header
        """
    def __init__(self, szaid: str, source: str, awr: float, temperature: float, date: str, comments: list[str]) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the header
            szaid         the szaid (max 24 characters)
            source        the source of the file
            awr           the atomic weight ratio (to the neutron mass)
            temperature   the temperature in MeV
            date          the date (max 10 characters)
            comments      the comments
        """
    def to_string(self) -> str:
        """
        Return the string representation of the ACE table
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def TEMP(self) -> float:
        """
        The temperature of the table
        """
    @property
    def VERS(self) -> str:
        """
        The header version
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def comments(self) -> list[str]:
        """
        The comments
        """
    @property
    def date(self) -> str:
        """
        The date
        """
    @property
    def temperature(self) -> float:
        """
        The temperature of the table
        """
    @property
    def version(self) -> str:
        """
        The header version
        """
    @property
    def zaid(self) -> str:
        """
        The full ZAID or SZAID of the table
        """
class PhotoatomicTable:
    """
    A thermal scattering ACE table
    
    The PhotoatomicTable class represents the ACE table for photoatomic data.
    """
    @staticmethod
    def from_concatenated_file(arg0: str) -> list[PhotoatomicTable]:
        """
        Read ACE tables from a concatenated file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    @staticmethod
    def from_file(arg0: str) -> PhotoatomicTable:
        """
        Read an ACE table from a file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    def EION(self, index: int) -> electron.EnergyDistributionBlock:
        """
        Return the knock-on electron energy distribution block for a subshell index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, z: int, header: Header | Header201, za: list[int], awr: list[float], eszg: photoatomic.PrincipalCrossSectionBlock, jinc: photoatomic.IncoherentScatteringFunctionBlock, jcoh: photoatomic.CoherentFormFactorBlock, lhnm: photoatomic.HeatingNumbersBlock, jflo: photoatomic.FluorescenceDataBlock | None = None, eps: electron.ElectronShellBlock | None = None, swd: photoatomic.ComptonProfileBlock | None = None, subsh: electron.ElectronSubshellBlock | None = None, sphel: photoatomic.PhotoelectricCrossSectionBlock | None = None, xprob: electron.SubshellTransitionDataBlock | None = None, esze: electron.PrincipalCrossSectionBlock | None = None, excit: electron.ExcitationBlock | None = None, elas: electron.ElasticAngularDistributionBlock | None = None, eion: list[electron.EnergyDistributionBlock] = [], breme: electron.EnergyDistributionBlock | None = None, breml: electron.BremsstrahlungBlock | None = None, selas: electron.ElasticCrossSectionBlock | None = None) -> None:
        """
        Initialise the table
        
        Arguments:
            self      the table
            z         the Z number of the target
            header    the header for the table
            za        the list of ZA values
            awr       the list of atomic mass values
            eszg      the principal cross section block
            jinc      the incoherent scattering function block
            jcoh      the coherent form factor block
            lhnm      the heating numbers block
            jflo      the fluorescence data block
            eps       the electron shell block
            swd       the compton profile block
            subsh     the electron subshell data block
            sphel     the photoelectric cross section block
            xprob     the atomic relaxation data block
            esze      the electron cross section block
            excit     the excitation energy loss data block
            elas      the electron elastic angular distribution block
            eion      the electronionisation data block
            breme     the photon energy distributions from Bremsstrahlung
            breml     the electron average energy after Bremsstrahlung
            selas     the additional electron elastic cross section block
        """
    def electroionisation_energy_distribution_block(self, index: int) -> electron.EnergyDistributionBlock:
        """
        Return the knock-on electron energy distribution block for a subshell index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def to_file(self, arg0: str) -> None:
        """
        Write the ACE table to a file
        
        Arguments:
            self        the table
            filename    the file name and path
        """
    @property
    def A() -> int:
        """
        The mass number of the target
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def BREME(self) -> electron.EnergyDistributionBlock | None:
        """
        The Bremsstrahlung energy distribution block for eprdata (NEPR > 0)
        """
    @property
    def BREML(self) -> electron.BremsstrahlungBlock | None:
        """
        The electron energy after Brehmsstrahlung block for eprdata (NEPR > 0)
        """
    @property
    def ELAS(self) -> electron.ElasticAngularDistributionBlock | None:
        """
        The electron elastic angular distribution block for eprdata (NEPR > 0)
        """
    @property
    def EPS(self) -> electron.ElectronShellBlock | None:
        """
        The electron shell block
        """
    @property
    def ESZE(self) -> electron.PrincipalCrossSectionBlock | None:
        """
        The electron cross section block for eprdata (NEPR > 0)
        """
    @property
    def ESZG(self) -> photoatomic.PrincipalCrossSectionBlock:
        """
        The principal cross section block
        """
    @property
    def EXCIT(self) -> electron.ExcitationBlock | None:
        """
        The electron excitation energy loss block for eprdata (NEPR > 0)
        """
    @property
    def JCOH(self) -> photoatomic.CoherentFormFactorBlock:
        """
        The coherent form factor block
        """
    @property
    def JFLO(self) -> photoatomic.FluorescenceDataBlock | None:
        """
        The fluorescence data block
        """
    @property
    def JINC(self) -> photoatomic.IncoherentScatteringFunctionBlock:
        """
        The incoherent scattering function block
        """
    @property
    def LHNM(self) -> photoatomic.HeatingNumbersBlock:
        """
        The heating numbers block
        """
    @property
    def NA(self) -> int:
        """
        The number of energy points with electron elastic angular distributions
        """
    @property
    def NB(self) -> int:
        """
        The number of energy points with Bremsstrahlung photon energy distributions
        """
    @property
    def NBL(self) -> int:
        """
        The number of electron Bremsstrahlung energy points
        """
    @property
    def NE(self) -> int:
        """
        The number of electron energy points
        """
    @property
    def NEPR(self) -> int:
        """
        The EPR data format flag (0 for the old mcplib format, 1 for EPR data from
        2012 and 3 for EPR data from 2014 and above)
        """
    @property
    def NES(self) -> int:
        """
        The number of energy points
        """
    @property
    def NFLO(self) -> int:
        """
        The number of fluorescence edges
        """
    @property
    def NSH(self) -> int:
        """
        The number of electron shells (for Compton Doppler broadening)
        """
    @property
    def NSSH(self) -> int:
        """
        The number of subshells for photoelectric and electron impact ionization
        """
    @property
    def NXL(self) -> int:
        """
        The number of electron excitation energy points
        """
    @property
    def S() -> int:
        """
        The isomeric state of the target
        """
    @property
    def SELAS(self) -> electron.ElasticCrossSectionBlock | None:
        """
        The additional elastic cross section block for eprdata (NEPR = 3)
        """
    @property
    def SPHEL(self) -> photoatomic.PhotoelectricCrossSectionBlock | None:
        """
        The photolectric cross section block for eprdata (NEPR > 0)
        """
    @property
    def SUBSH(self) -> electron.ElectronSubshellBlock | None:
        """
        The electron subshell data block for eprdata (NEPR > 0)
        """
    @property
    def SWD(self) -> photoatomic.ComptonProfileBlock | None:
        """
        The compton profile block
        """
    @property
    def TEMP(self) -> float:
        """
        The temperature of the table
        """
    @property
    def XPROB(self) -> electron.SubshellTransitionDataBlock | None:
        """
        The subshell transition data block for eprdata (NEPR > 0)
        """
    @property
    def Z(self) -> int:
        """
        The atom number of the target
        """
    @property
    def atom_number(self) -> int:
        """
        The atom number of the target
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def bremsstrahlung_energy_distribution_block(self) -> electron.EnergyDistributionBlock | None:
        """
        The Bremsstrahlung energy distribution block for eprdata (NEPR > 0)
        """
    @property
    def coherent_form_factor_block(self) -> photoatomic.CoherentFormFactorBlock:
        """
        The coherent form factor block
        """
    @property
    def compton_profile_block(self) -> photoatomic.ComptonProfileBlock | None:
        """
        The electron shell block
        """
    @property
    def data(self) -> Data:
        """
        The data arrays
        """
    @property
    def date(self) -> str:
        """
        The date
        """
    @property
    def electron_cross_section_block(self) -> electron.PrincipalCrossSectionBlock | None:
        """
        The electron cross section block for eprdata (NEPR > 0)
        """
    @property
    def electron_elastic_angular_distribution_block(self) -> electron.ElasticAngularDistributionBlock | None:
        """
        The electron elastic angular distribution block for eprdata (NEPR > 0)
        """
    @property
    def electron_elastic_cross_section_block(self) -> electron.ElasticCrossSectionBlock | None:
        """
        The additional elastic cross section block for eprdata (NEPR = 3)
        """
    @property
    def electron_energy_after_bremsstrahlung_block(self) -> electron.BremsstrahlungBlock | None:
        """
        The electron energy after Brehmsstrahlung block for eprdata (NEPR > 0)
        """
    @property
    def electron_excitation_energy_loss_block(self) -> electron.ExcitationBlock | None:
        """
        The electron excitation energy loss block for eprdata (NEPR > 0)
        """
    @property
    def electron_photon_relaxation_format(self) -> int:
        """
        The EPR data format flag (0 for the old mcplib format, 1 for EPR data from
        2012 and 3 for EPR data from 2014 and above)
        """
    @property
    def electron_shell_block(self) -> electron.ElectronShellBlock | None:
        """
        The electron shell block
        """
    @property
    def electron_subshell_block(self) -> electron.ElectronSubshellBlock | None:
        """
        The electron subshell data block for eprdata (NEPR > 0)
        """
    @property
    def fluorescence_data_block(self) -> photoatomic.FluorescenceDataBlock | None:
        """
        The fluorescence data block
        """
    @property
    def header(self) -> Header | Header201:
        """
        The header information
        """
    @property
    def heating_numbers_block(self) -> photoatomic.HeatingNumbersBlock:
        """
        The heating numbers block
        """
    @property
    def incoherent_scattering_function_block(self) -> photoatomic.IncoherentScatteringFunctionBlock:
        """
        The incoherent scattering function block
        """
    @property
    def isomeric_state() -> int:
        """
        The isomeric state of the target
        """
    @property
    def length(self) -> int:
        """
        The total length of the XSS array
        """
    @property
    def mass_number() -> int:
        """
        The mass number of the target
        """
    @property
    def number_electron_bremsstrahlung_energy_points(self) -> int:
        """
        The number of electron Bremsstrahlung energy points
        """
    @property
    def number_electron_elastic_energy_points(self) -> int:
        """
        The number of energy points with electron elastic angular distributions
        """
    @property
    def number_electron_energy_points(self) -> int:
        """
        The number of electron energy points
        """
    @property
    def number_electron_excitation_energy_points(self) -> int:
        """
        The number of electron excitation energy points
        """
    @property
    def number_electron_shells(self) -> int:
        """
        The number of electron shells (for Compton Doppler broadening)
        """
    @property
    def number_electron_subshells(self) -> int:
        """
        The number of subshells for photoelectric and electron impact ionization
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of energy points
        """
    @property
    def number_fluorescence_edges(self) -> int:
        """
        The number of fluorescence edges
        """
    @property
    def photoelectric_cross_section_block(self) -> photoatomic.PhotoelectricCrossSectionBlock | None:
        """
        The photolectric cross section block for eprdata (NEPR > 0)
        """
    @property
    def principal_cross_section_block(self) -> photoatomic.PrincipalCrossSectionBlock:
        """
        The principal cross section block
        """
    @property
    def subshell_transition_data_block(self) -> electron.SubshellTransitionDataBlock | None:
        """
        The subshell transition data block for eprdata (NEPR > 0)
        """
    @property
    def temperature(self) -> float:
        """
        The temperature of the table
        """
    @property
    def zaid(self) -> str:
        """
        The full ZAID or SZAID of the table
        """
class PhotonuclearTable:
    """
    A continuous energy ACE table
    
    The PhotonuclearTable class represents the ACE table for the photonuclear data.
    """
    @staticmethod
    def from_concatenated_file(arg0: str) -> list[PhotonuclearTable]:
        """
        Read ACE tables from a concatenated file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    @staticmethod
    def from_file(arg0: str) -> PhotonuclearTable:
        """
        Read an ACE table from a file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    def ANDH(self, index: int) -> continuous.SecondaryParticleAngularDistributionBlock:
        """
        Return the angular distribution block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def DLWH(self, index: int) -> continuous.SecondaryParticleEnergyDistributionBlock:
        """
        Return the energy distribution block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def MTRH(self, index: int) -> continuous.ReactionNumberBlock:
        """
        Return the reaction number block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def PHN(self, index: int) -> continuous.CrossSectionData:
        """
        Return the secondary particle average heating cross section for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def PXS(self, index: int) -> continuous.CrossSectionData:
        """
        Return the secondary particle production cross section for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def SIGH(self, index: int) -> continuous.SecondaryParticleProductionCrossSectionBlock:
        """
        Return the production cross section block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def TYRH(self, index: int) -> continuous.FrameAndMultiplicityBlock:
        """
        Return the reference frame and multiplicity block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, z: int, a: int, s: int, header: Header | Header201, eszu: photonuclear.PrincipalCrossSectionBlock, mtr: continuous.ReactionNumberBlock, lqr: continuous.ReactionQValueBlock, sig: continuous.CrossSectionBlock, ptype: list[int] | None = None, pxs: list[continuous.CrossSectionData] | None = None, phn: list[continuous.CrossSectionData] | None = None, mtrh: list[continuous.ReactionNumberBlock] | None = None, sigh: list[continuous.SecondaryParticleProductionCrossSectionBlock] | None = None, andh: list[continuous.SecondaryParticleAngularDistributionBlock] | None = None, dlwh: list[continuous.SecondaryParticleEnergyDistributionBlock] | None = None) -> None:
        """
        Initialise the table
        
        Arguments:
            self      the table
            z         the Z number of the target
            a         the A number of the target
            s         the S number of the target
            header    the header for the table
            eszu      the principal cross section block
            mtr       the reaction number block
            lqr       the reaction Q value block
            sig       the cross section data block
            ptype     the secondary particle types
            pxs       the secondary particle production cross section data
            phn       the secondary particle heating cross section data
            mtrh      the secondary particle production reaction number blocks
            sigh      the secondary particle production cross section data blocks
            andh      the secondary particle angular distribution data blocks
            dlwh      the secondary particle energy distribution data blocks
        """
    def secondary_particle_angular_distribution_block(self, index: int) -> continuous.SecondaryParticleAngularDistributionBlock:
        """
        Return the angular distribution block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_energy_distribution_block(self, index: int) -> continuous.SecondaryParticleEnergyDistributionBlock:
        """
        Return the energy distribution block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_frame_and_multiplicity_block(self, index: int) -> continuous.FrameAndMultiplicityBlock:
        """
        Return the reference frame and multiplicity block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_heating_cross_section(self, index: int) -> continuous.CrossSectionData:
        """
        Return the secondary particle average heating cross section for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_production_crossSection(self, index: int) -> continuous.CrossSectionData:
        """
        Return the secondary particle production cross section for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_production_cross_section_block(self, index: int) -> continuous.SecondaryParticleProductionCrossSectionBlock:
        """
        Return the production cross section block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def secondary_particle_reaction_number_block(self, index: int) -> continuous.ReactionNumberBlock:
        """
        Return the reaction number block for a secondary particle index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def to_file(self, arg0: str) -> None:
        """
        Write the ACE table to a file
        
        Arguments:
            self        the table
            filename    the file name and path
        """
    @property
    def A(self) -> int:
        """
        The mass number of the target
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def ESZ(self) -> photonuclear.PrincipalCrossSectionBlock:
        """
        The principal cross section block
        """
    @property
    def IXS(self) -> photonuclear.SecondaryParticleLocatorBlock | None:
        """
        The secondary particle information and locator block
        """
    @property
    def LQR(self) -> continuous.ReactionQValueBlock:
        """
        The reaction Q value block
        """
    @property
    def MTR(self) -> continuous.ReactionNumberBlock:
        """
        The reaction number block
        """
    @property
    def NES(self) -> int:
        """
        The number of energy points
        """
    @property
    def NTR(self) -> int:
        """
        The number of available reactions
        """
    @property
    def NTYPE(self) -> int:
        """
        The number of secondary particle types
        """
    @property
    def S(self) -> int:
        """
        The isomeric state of the target
        """
    @property
    def SIG(self) -> continuous.CrossSectionBlock:
        """
        The cross section block
        """
    @property
    def TEMP(self) -> float:
        """
        The temperature of the table
        """
    @property
    def Z(self) -> int:
        """
        The atom number of the target
        """
    @property
    def atom_number(self) -> int:
        """
        The atom number of the target
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def cross_section_block(self) -> continuous.CrossSectionBlock:
        """
        The cross section block
        """
    @property
    def data(self) -> Data:
        """
        The data arrays
        """
    @property
    def date(self) -> str:
        """
        The date
        """
    @property
    def header(self) -> Header | Header201:
        """
        The header information
        """
    @property
    def isomeric_state(self) -> int:
        """
        The isomeric state of the target
        """
    @property
    def length(self) -> int:
        """
        The total length of the XSS array
        """
    @property
    def mass_number(self) -> int:
        """
        The mass number of the target
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of energy points
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of available reactions
        """
    @property
    def number_secondary_particle_types(self) -> int:
        """
        The number of secondary particle types
        """
    @property
    def principal_cross_section_block(self) -> photonuclear.PrincipalCrossSectionBlock:
        """
        The principal cross section block
        """
    @property
    def reaction_number_block(self) -> continuous.ReactionNumberBlock:
        """
        The reaction number block
        """
    @property
    def reaction_qvalue_block(self) -> continuous.ReactionQValueBlock:
        """
        The reaction Q value block
        """
    @property
    def secondary_particle_locator_block(self) -> photonuclear.SecondaryParticleLocatorBlock | None:
        """
        The secondary particle information and locator block
        """
    @property
    def temperature(self) -> float:
        """
        The temperature of the table
        """
    @property
    def za(self) -> int:
        """
        The ZA of the target
        """
    @property
    def zaid(self) -> str:
        """
        The full ZAID or SZAID of the table
        """
class ReferenceFrame:
    """
    The reference frame for the angular and energy distributions
    
    Members:
    
      CentreOfMass
    
      Laboratory
    """
    CentreOfMass: typing.ClassVar[ReferenceFrame]  # value = <ReferenceFrame.CentreOfMass: 1>
    Laboratory: typing.ClassVar[ReferenceFrame]  # value = <ReferenceFrame.Laboratory: 0>
    __members__: typing.ClassVar[dict[str, ReferenceFrame]]  # value = {'CentreOfMass': <ReferenceFrame.CentreOfMass: 1>, 'Laboratory': <ReferenceFrame.Laboratory: 0>}
    def __eq__(self, other: typing.Any) -> bool:
        ...
    def __ge__(self, other: typing.Any) -> bool:
        ...
    def __getstate__(self) -> int:
        ...
    def __gt__(self, other: typing.Any) -> bool:
        ...
    def __hash__(self) -> int:
        ...
    def __index__(self) -> int:
        ...
    def __init__(self, value: int) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __le__(self, other: typing.Any) -> bool:
        ...
    def __lt__(self, other: typing.Any) -> bool:
        ...
    def __ne__(self, other: typing.Any) -> bool:
        ...
    def __repr__(self) -> str:
        ...
    def __setstate__(self, state: int) -> None:
        ...
    def __str__(self) -> str:
        ...
    @property
    def name(self) -> str:
        ...
    @property
    def value(self) -> int:
        ...
class Table:
    """
    A generic ACE table
    
    A Table represents the generic ACE table, which can be of any type
    (e.g. continuous energy, thermal scattering, etc.). It contains a header
    and the actual data of the table (the data being the IZAW, NXS, JXS and XSS
    arrays).
    """
    @staticmethod
    def from_file(arg0: str) -> Table:
        """
        Read an ACE table from a file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    @staticmethod
    def from_string(string: str) -> Table:
        """
        Read the ACE table from a string
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            string    the string representing the ACE table
        """
    def __init__(self, header: Header | Header201, data: Data) -> None:
        """
        Initialise the component
        
        Arguments:
            self     the table
            header   the header information
            data     the ACE data
        """
    def to_file(self, arg0: str) -> None:
        """
        Write the ACE table to a file
        
        Arguments:
            self        the table
            filename    the file name and path
        """
    def to_string(self) -> str:
        """
        Return the string representation of the ACE table
        """
    @property
    def data(self) -> Data:
        """
        The data arrays
        """
    @property
    def header(self) -> Header | Header201:
        """
        The header information
        """
class ThermalScatteringTable:
    """
    A thermal scattering ACE table
    
    The ThermalScatteringTable class represents the ACE table for thermal
    scattering data.
    """
    @staticmethod
    def from_concatenated_file(arg0: str) -> list[ThermalScatteringTable]:
        """
        Read ACE tables from a concatenated file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    @staticmethod
    def from_file(arg0: str) -> ThermalScatteringTable:
        """
        Read an ACE table from a file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    def __init__(self, header: Header, za: list[int], itie: thermal.CrossSectionBlock, itxe: thermal.InelasticAngularDistributionBlock, itce: thermal.CrossSectionBlock | None = None, itca: thermal.ElasticAngularDistributionBlock | None = None, itcei: thermal.CrossSectionBlock | None = None, itcai: thermal.ElasticAngularDistributionBlock | None = None) -> None:
        """
        Initialise the table
        
        Arguments:
            self      the table
            header    the header for the table
            za        the list of ZA values
            itie      the inelastic thermal scattering cross section block
            itxe      the inelastic thermal scattering angular distribution block
            itce      the coherent elastic thermal scattering cross section block
            itca      the coherent elastic thermal scattering angular distribution block
            itcei     the incoherent elastic thermal scattering cross section block
            itcai     the incoherent elastic thermal scattering angular distribution block
        """
    def to_file(self, arg0: str) -> None:
        """
        Write the ACE table to a file
        
        Arguments:
            self        the table
            filename    the file name and path
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def IDPNC(self) -> int:
        """
        The elastic scattering mode
        """
    @property
    def IDPNI(self) -> int:
        """
        The inelastic scattering mode
        """
    @property
    def IFENG(self) -> int:
        """
        The secondary energy mode
        """
    @property
    def ITCA(self) -> thermal.ElasticAngularDistributionBlock | None:
        """
        The coherent elastic thermal scattering angular distribution block
        """
    @property
    def ITCAI(self) -> thermal.ElasticAngularDistributionBlock | None:
        """
        The incoherent elastic thermal scattering angular distribution block
        """
    @property
    def ITCE(self) -> thermal.CrossSectionBlock | None:
        """
        The coherent elastic thermal scattering cross section block
        """
    @property
    def ITCEI(self) -> thermal.CrossSectionBlock | None:
        """
        The incoherent elastic thermal scattering cross section block
        """
    @property
    def ITIE(self) -> thermal.CrossSectionBlock:
        """
        The inelastic thermal scattering cross section block
        """
    @property
    def ITXE(self) -> thermal.InelasticAngularDistributionBlock:
        """
        The inelastic thermal scattering angular distribution block
        """
    @property
    def NCL(self) -> int:
        """
        The first elastic dimensioning parameter
        
        The elastic dimensioning parameter is equal to NC - 1
        """
    @property
    def NCLI(self) -> int:
        """
        The second elastic dimensioning parameter
        
        The elastic dimensioning parameter is equal to NC - 1
        """
    @property
    def NIEB(self) -> int:
        """
        The number of inelastic outgoing energies
        """
    @property
    def NIL(self) -> int:
        """
        The inelastic dimensioning parameter
        
        For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,
        for IFENG = 2 this will be equal to NC + 1
        """
    @property
    def TEMP(self) -> float:
        """
        The temperature of the table
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def coherent_elastic_angular_distribution_block(self) -> thermal.ElasticAngularDistributionBlock | None:
        """
        The incoherent elastic thermal scattering angular distribution block
        """
    @property
    def coherent_elastic_cross_section_block(self) -> thermal.CrossSectionBlock | None:
        """
        The coherent elastic thermal scattering cross section block
        """
    @property
    def data(self) -> Data:
        """
        The data arrays
        """
    @property
    def date(self) -> str:
        """
        The date
        """
    @property
    def elastic_scattering_mode(self) -> int:
        """
        The elastic scattering mode
        """
    @property
    def first_elastic_dimensioning_parameter(self) -> int:
        """
        The first elastic dimensioning parameter
        
        The elastic dimensioning parameter is equal to NC - 1
        """
    @property
    def header(self) -> Header | Header201:
        """
        The header information
        """
    @property
    def incoherent_elastic_angular_distribution_block(self) -> thermal.ElasticAngularDistributionBlock | None:
        """
        The incoherent elastic thermal scattering angular distribution block
        """
    @property
    def incoherent_elastic_cross_section_block(self) -> thermal.CrossSectionBlock | None:
        """
        The incoherent elastic thermal scattering cross section block
        """
    @property
    def inelastic_angular_distribution_block(self) -> thermal.InelasticAngularDistributionBlock:
        """
        The inelastic thermal scattering angular distribution block
        """
    @property
    def inelastic_cross_section_block(self) -> thermal.CrossSectionBlock:
        """
        The inelastic thermal scattering cross section block
        """
    @property
    def inelastic_dimensioning_parameter(self) -> int:
        """
        The inelastic dimensioning parameterFor IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,
        for IFENG = 2 this will be equal to NC + 1
        """
    @property
    def inelastic_scattering_mode(self) -> int:
        """
        The inelastic scattering mode
        """
    @property
    def length(self) -> int:
        """
        The total length of the XSS array
        """
    @property
    def number_inelastic_outgoing_energies(self) -> int:
        """
        The number of inelastic outgoing energies
        """
    @property
    def second_elastic_dimensioning_parameter(self) -> int:
        """
        The second elastic dimensioning parameter
        
        The elastic dimensioning parameter is equal to NC - 1
        """
    @property
    def secondary_energy_mode(self) -> int:
        """
        The secondary energy mode
        """
    @property
    def temperature(self) -> float:
        """
        The temperature of the table
        """
    @property
    def zaid(self) -> str:
        """
        The full ZAID or SZAID of the table
        """
class Xsdir:
    """
    An xsdir file
    
    An xsdir file consists of the following:
      - an optional data path
      - a set of atomic weight values
      - a set of xsdir entries
    """
    @staticmethod
    def from_file(arg0: str) -> Xsdir:
        """
        Read an xsdir from a file
        
        An exception is raised if something goes wrong while reading the xsdir
        
        Arguments:
            filename    the file name and path
        """
    @staticmethod
    def from_string(string: str) -> Xsdir:
        """
        Read the xsdir from a string
        
        An exception is raised if something goes wrong while reading the xsdir
        
        Arguments:
            string    the string representing the xsdir
        """
    def __init__(self, ratios: dict[int, float], entries: list[XsdirEntry], datapath: str | None = None) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the xsdir
            ratios     the atomic weight ratios
            entries    the file name
            datapath   the optional datapath
        """
    def atomic_weight_ratio(self, za: int) -> float:
        """
        The atomic weight ratio for a given za
        """
    def entry(self, zaid: str) -> XsdirEntry:
        """
        The xsdir entry for a given ZAID
        """
    def to_file(self, arg0: str) -> None:
        """
        Write the xsdir to a file
        
        Arguments:
            self        the xsdir
            filename    the file name and path
        """
    def to_string(self) -> str:
        """
        Return the string representation of the xsdir
        """
    @property
    def atomic_weight_ratios(self) -> dict[int, float]:
        """
        The atomic weight ratios
        """
    @property
    def data_path(self) -> str | None:
        """
        The optional datapath
        """
    @property
    def entries(self) -> list[XsdirEntry]:
        """
        The xsdir entries
        """
class XsdirEntry:
    """
    An entry in an xsdir file
    
    An xsdir entry consists of either 7, 10 or 11 values:
      - the zaid
      - the atomic mass ratio
      - file name
      - an access path (undefined path if '0')
      - a file type (1 for ascii, 2 for binary)
      - the starting address or line number
      - the table length (number of words in the XSS array)
      - the length of a record (0 for ascii files)
      - the number of entries (0 for ascii files)
      - the temperature in MeV
      - ptable if the table has a probability table for the URR
    """
    @staticmethod
    def from_string(string: str) -> XsdirEntry:
        """
        Read the xsdir entry from a string
        
        An exception is raised if something goes wrong while reading the entry
        
        Arguments:
            string    the string representing the xsdir entry
        """
    @typing.overload
    def __init__(self, zaid: str, awr: float, filename: str, filetype: int, address: int, length: int, access: str | None = None, recordlength: int | None = None, entries: int | None = None, temperature: float | None = None, ptable: bool = False) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the xsdir entry
            zaid            the zaid
            awr             the atomic weight ratio (to the neutron mass)
            filename        the file name
            address         the starting address or line
            length          the length of the file
            access          the access path for the file (optional)
            recordlength    the length of a record (optional)
            entries         the number of entries per record (optional)
            temperature     the temperature of the file (optional)
            ptable          flag to indicate if a probability table is present
        """
    @typing.overload
    def __init__(self, zaid: str, awr: float, filename: str, address: int, length: int, temperature: float | None = None, ptable: bool = False, access: str | None = None) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the xsdir entry
            zaid            the zaid
            awr             the atomic weight ratio (to the neutron mass)
            filename        the file name
            address         the starting address or line
            length          the length of the file
            temperature     the temperature of the file (optional)
            ptable          flag to indicate if a probability table is present
            access          the access path for the file (optional)
        """
    def to_string(self) -> str:
        """
        Return the string representation of the xsdir entry
        """
    @property
    def access_route(self) -> str | None:
        """
        The access route
        """
    @property
    def address(self) -> int:
        """
        The table address or starting line
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def awr(self) -> float:
        """
        The atomic weight ratio (with respect to the neutron mass)
        """
    @property
    def entries_per_record(self) -> int | None:
        """
        The number of entries per record (used for binary files only)
        """
    @property
    def file_name(self) -> str:
        """
        The file name and path
        """
    @property
    def file_type(self) -> int:
        """
        The file type
        """
    @property
    def ptable(self) -> bool:
        """
        The flag indicating whether or not a probability table is present
        """
    @property
    def record_length(self) -> int | None:
        """
        The record length (used for binary files only)
        """
    @property
    def table_length(self) -> int:
        """
        The table length
        """
    @property
    def temperature(self) -> float | None:
        """
        The temperature of the table (if it is defined)
        """
    @property
    def zaid(self) -> str:
        """
        The ZAID of the table
        """
